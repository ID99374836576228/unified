#include "nwnx.hpp"

#include "API/Globals.hpp"
#include "API/Constants.hpp"
#include "API/CGameEffect.hpp"
#include "API/CNWSObject.hpp"
#include "API/CAppManager.hpp"
#include "API/CServerExoApp.hpp"
#include "API/CNWSCreature.hpp"
#include "API/CNWSCombatRound.hpp"
#include "API/CNWSEffectListHandler.hpp"
#include "API/CNWRules.hpp"
#include "API/CNWCCMessageData.hpp"

#include <cstring>
#include <bitset>

using namespace NWNXLib;
using namespace NWNXLib::API;

constexpr int32_t MAX_DAMAGE_TYPES = 32;

struct DamageData
{
    uint32_t oidDamager;
    int32_t vDamage[MAX_DAMAGE_TYPES];
    int32_t nSpellId;
};

struct AttackData
{
    uint32_t oidTarget;
    int16_t vDamage[MAX_DAMAGE_TYPES];
    uint8_t nAttackNumber;
    uint8_t nAttackResult;
    uint8_t nWeaponAttackType;
    uint8_t nSneakAttack;
    uint8_t bRanged;
    int32_t bKillingBlow;
    uint16_t nAttackType;
    uint8_t nToHitRoll;
    int32_t nToHitModifier;
};

static std::unordered_map<std::string, std::string> s_EventScriptMap;
static DamageData s_DamageData;
static AttackData s_AttackData;

static std::string GetEventScript(CNWSObject*, const std::string&);
static void HandleSignalDamage(CNWSCreature*, CNWSObject*, int32_t);

static Hooks::Hook s_OnApplyDamageHook = Hooks::HookFunction(&CNWSEffectListHandler::OnApplyDamage,
    +[](CNWSEffectListHandler *pThis, CNWSObject *pObject, CGameEffect *pEffect, BOOL bLoadingGame) -> BOOL
    {
        std::string sScript = GetEventScript(pObject, "DAMAGE");

        if (!sScript.empty())
        {
            if (Utils::AsNWSCreature(pObject) || Utils::AsNWSPlaceable(pObject) || Utils::AsNWSDoor(pObject))
            {
                s_DamageData.oidDamager = pEffect->m_oidCreator;
                std::memcpy(s_DamageData.vDamage, pEffect->m_nParamInteger, MAX_DAMAGE_TYPES * sizeof(int32_t));
                s_DamageData.nSpellId = pEffect->m_nSpellId;
                Utils::ExecuteScript(sScript, pObject->m_idSelf);
                std::memcpy(pEffect->m_nParamInteger, s_DamageData.vDamage, MAX_DAMAGE_TYPES * sizeof(int32_t));
            }
        }

       return s_OnApplyDamageHook->CallOriginal<BOOL>(pThis, pObject, pEffect, bLoadingGame);
    }, Hooks::Order::Late);

static Hooks::Hook s_SignalMeleeDamageHook = Hooks::HookFunction(&CNWSCreature::SignalMeleeDamage,
    +[](CNWSCreature *pThis, CNWSObject *pTarget, int32_t nAttacks) -> void
    {
        HandleSignalDamage(pThis, pTarget, nAttacks);
        s_SignalMeleeDamageHook->CallOriginal<void>(pThis, pTarget, nAttacks);
    }, Hooks::Order::Late);

static Hooks::Hook s_SignalRangedDamageHook = Hooks::HookFunction(&CNWSCreature::SignalRangedDamage,
    +[](CNWSCreature *pThis, CNWSObject *pTarget, int32_t nAttacks) -> void
    {
        HandleSignalDamage(pThis, pTarget, nAttacks);
        s_SignalRangedDamageHook->CallOriginal<void>(pThis, pTarget, nAttacks);
    }, Hooks::Order::Late);
	
static Hooks::Hook s_ResolveAttackRollHook = Hooks::HookFunction(&CNWSCreature::ResolveAttackRoll,
    (void*)+[](CNWSCreature *pThis, CNWSObject *pTarget) -> void
{
	if (!pTarget)
		return;

	CNWSCombatRound *pCombatRound = pThis->m_pcCombatRound;
	CNWSCombatAttackData *pAttackData = pCombatRound->GetAttack(pCombatRound->m_nCurrentAttack);
	int32_t nAttackRoll = Globals::Rules()->RollDice(1, 20);

	// DEBUG
	if (Globals::EnableCombatDebugging())
	{
		pAttackData->m_sAttackDebugText.Format("%s Attack Roll: %d", pThis->m_pStats->GetFullName().CStr(), nAttackRoll);
	}
	// /////

	CNWSCreature *pCreature = Utils::AsNWSCreature(pTarget);
	int32_t nAttackRollModifier, nArmorClass;

	if (pCreature)
	{
		nAttackRollModifier = pThis->m_pStats->GetAttackModifierVersus(pCreature);
		nArmorClass = pCreature->m_pStats->GetArmorClassVersus(pThis);
	}
	else
	{
		nAttackRollModifier = pThis->m_pStats->GetAttackModifierVersus();
		nArmorClass = 0;
	}

	// DEBUG
	if (Globals::EnableCombatDebugging())
	{
		CExoString sCurrent = pAttackData->m_sAttackDebugText;
		CExoString sAdd;

		sAdd.Format(" Versus AC %d", nArmorClass);
		pAttackData->m_sAttackDebugText = sCurrent + sAdd;
	}
	// /////

	if (pCreature)
	{
		pThis->ResolveSneakAttack(pCreature);
		pThis->ResolveDeathAttack(pCreature);
	}

	if (pAttackData->m_bCoupDeGrace)
	{
		pAttackData->m_nToHitRoll = 20;
		pAttackData->m_nToHitMod = nAttackRollModifier;
		pAttackData->m_nAttackResult = 7;/*Automatic Hit*/
		return;
	}

	pAttackData->m_nToHitRoll = nAttackRoll;
	pAttackData->m_nToHitMod = nAttackRollModifier;

	if (pThis->ResolveDefensiveEffects(pTarget, (nAttackRoll + nAttackRollModifier >= nArmorClass)))
		return;

	// Parry Check
	if (pCreature)
	{
		if (nAttackRoll != 20)
		{
			if (pCreature->m_nCombatMode == Constants::CombatMode::Parry &&
				pCreature->m_pcCombatRound->m_nParryActions > 0 &&
				!pCreature->m_pcCombatRound->m_bRoundPaused &&
				pCreature->m_nState != 6/*Stunned*/ &&
				!pAttackData->m_bRangedAttack &&
				!pCreature->GetRangeWeaponEquipped())
			{
				static int32_t nParryRiposteDifference = Globals::Rules()->GetRulesetIntEntry(CRULES_HASHEDSTR("PARRY_RIPOSTE_DIFFERENCE"), 10);
				int32_t nParryRoll = Globals::Rules()->RollDice(1, 20) +
						pCreature->m_pStats->GetSkillRank(Constants::Skill::Parry, Utils::AsNWSObject(pThis));

				if (nParryRoll >= nAttackRoll + nAttackRollModifier)
				{
					if (nParryRoll - nParryRiposteDifference >= nAttackRoll + nAttackRollModifier)
					{
						pCreature->m_pcCombatRound->AddParryAttack(pThis->m_idSelf);
					}

					pAttackData->m_nAttackResult = 2;/*Parried*/
					pCreature->m_pcCombatRound->m_nParryActions--;
					return;
				}

				pCreature->m_pcCombatRound->AddParryIndex();
				pCreature->m_pcCombatRound->m_nParryActions--;
			}
		}
	}

	if (nAttackRoll != 1)
	{
		if ((nAttackRoll + nAttackRollModifier >= nArmorClass) || nAttackRoll == 20)
		{
			if (nAttackRoll >= pThis->m_pStats->GetCriticalHitRoll(pCombatRound->GetOffHandAttack()))
			{
				int32_t nCriticalHitRoll = Globals::Rules()->RollDice(1, 20);

				pAttackData->m_bCriticalThreat = true;
				pAttackData->m_nThreatRoll = nCriticalHitRoll;

				if (nCriticalHitRoll + nAttackRollModifier >= nArmorClass)
				{
					if (pCreature)
					{
						if (Globals::AppManager()->m_pServerExoApp->GetDifficultyOption(0/*No Critical Hits On PCs*/))
						{
							if (pCreature->m_bPlayerCharacter && !pThis->m_bPlayerCharacter)
							{
								pAttackData->m_nAttackResult = 1;/*Successful Hit*/
								return;
							}
						}

						if (pCreature->m_pStats->GetEffectImmunity(Constants::ImmunityType::CriticalHit, pThis))
						{
							auto *pData = new CNWCCMessageData;
							pData->SetObjectID(0, pCreature->m_idSelf);
							pData->SetInteger(0, 126/*Critical Hit Immunity Feedback*/);

							pAttackData->m_alstPendingFeedback.Add(pData);
							pAttackData->m_nAttackResult = 1;/*Successful Hit*/
							return;
						}
					}

					pAttackData->m_nAttackResult = 3;/*Critical Hit*/
					return;
				}
			}

			pAttackData->m_nAttackResult = 1;/*Successful Hit*/
			return;
		}
	}

	pAttackData->m_nAttackResult = 4;/*Miss*/

	if (nAttackRoll == 1)
		pAttackData->m_nMissedBy = 1;
	else
		pAttackData->m_nMissedBy = std::abs(nAttackRoll + nAttackRollModifier - nArmorClass);

}, Hooks::Order::Final);	

static std::string GetEventScript(CNWSObject *pObject, const std::string& sEventType)
{
    if (auto posScript = pObject->nwnxGet<std::string>(sEventType + "_EVENT_SCRIPT"))
        return *posScript;
    else
        return s_EventScriptMap[sEventType];
}

static void OnCombatAttack(CNWSCreature *pThis, CNWSObject *pTarget, const std::string& sScript, uint8_t nAttackNumber)
{
    CNWSCombatAttackData *pCombatAttackData = pThis->m_pcCombatRound->GetAttack(nAttackNumber);

    s_AttackData.oidTarget = pTarget->m_idSelf;
    s_AttackData.nAttackNumber = nAttackNumber + 1; // 1-based for backwards compatibility
    s_AttackData.nAttackResult = pCombatAttackData->m_nAttackResult;
    s_AttackData.nWeaponAttackType = pCombatAttackData->m_nWeaponAttackType;
    s_AttackData.nSneakAttack = pCombatAttackData->m_bSneakAttack + (pCombatAttackData->m_bDeathAttack << 1);
    s_AttackData.bKillingBlow = pCombatAttackData->m_bKillingBlow;
    s_AttackData.nAttackType = pCombatAttackData->m_nAttackType;
    s_AttackData.nToHitRoll = pCombatAttackData->m_nToHitRoll;
    s_AttackData.nToHitModifier = pCombatAttackData->m_nToHitMod;

    std::memcpy(s_AttackData.vDamage, pCombatAttackData->m_nDamage, MAX_DAMAGE_TYPES * sizeof(int16_t));
    Utils::ExecuteScript(sScript, pThis->m_idSelf);
    std::memcpy(pCombatAttackData->m_nDamage, s_AttackData.vDamage, MAX_DAMAGE_TYPES * sizeof(int16_t));

    pCombatAttackData->m_nAttackResult = s_AttackData.nAttackResult;
    pCombatAttackData->m_bSneakAttack = (s_AttackData.nSneakAttack & 1) == 1;
    pCombatAttackData->m_bDeathAttack = (s_AttackData.nSneakAttack & 2) == 2;
}

static void HandleSignalDamage(CNWSCreature *pThis, CNWSObject *pTarget, int32_t nAttacks)
{
    std::string sScript = GetEventScript(pThis, "ATTACK");
    if (!sScript.empty())
    {
        // m_nCurrentAttack points to the attack *after* this flurry
        uint8_t nAttackNumberOffset = pThis->m_pcCombatRound->m_nCurrentAttack - nAttacks;
        // trigger script once per attack in the flurry
        for (int32_t i = 0; i < nAttacks; i++)
            OnCombatAttack(pThis, pTarget, sScript, nAttackNumberOffset + i);
    }
}

NWNX_EXPORT ArgumentStack SetEventScript(ArgumentStack&& args)
{
    const auto sEvent = args.extract<std::string>();
    const auto sScript = args.extract<std::string>();
    const auto oidTarget = args.extract<ObjectID>();

    if (oidTarget == Constants::OBJECT_INVALID)
    {
        s_EventScriptMap[sEvent] = sScript;
        LOG_INFO("Set Global %s Event Script to %s", sEvent, sScript);
    }
    else
    {
        if (auto pTarget = Utils::GetGameObject(oidTarget))
        {
            if (!sScript.empty())
            {
                pTarget->nwnxSet(sEvent + "_EVENT_SCRIPT", sScript, true);
                LOG_INFO("Set object %s %s Event Script to %s", Utils::ObjectIDToString(oidTarget), sEvent, sScript);
            }
            else
            {
                pTarget->nwnxRemove(sEvent + "_EVENT_SCRIPT");
                LOG_INFO("Clearing %s Event Script for object %s", sEvent, Utils::ObjectIDToString(oidTarget));
            }
        }
    }

    return {};
}

NWNX_EXPORT ArgumentStack GetDamageEventData(ArgumentStack&&)
{
    ArgumentStack stack;

    ScriptAPI::InsertArgument(stack, s_DamageData.nSpellId);
    for (int k = (MAX_DAMAGE_TYPES - 1); k >= 0; k--)
    {
        ScriptAPI::InsertArgument(stack, s_DamageData.vDamage[k]);
    }
    ScriptAPI::InsertArgument(stack, s_DamageData.oidDamager);

    return stack;
}

NWNX_EXPORT ArgumentStack SetDamageEventData(ArgumentStack&& args)
{
    for (int &k : s_DamageData.vDamage)
    {
        k = args.extract<int32_t>();
    }

    return {};
}

NWNX_EXPORT ArgumentStack GetAttackEventData(ArgumentStack&&)
{
    ArgumentStack stack;

    ScriptAPI::InsertArgument(stack, s_AttackData.nToHitModifier);
    ScriptAPI::InsertArgument(stack, s_AttackData.nToHitRoll);
    ScriptAPI::InsertArgument(stack, s_AttackData.nAttackType);
    ScriptAPI::InsertArgument(stack, s_AttackData.bKillingBlow);
    ScriptAPI::InsertArgument(stack, s_AttackData.nSneakAttack);
    ScriptAPI::InsertArgument(stack, s_AttackData.nWeaponAttackType);
    ScriptAPI::InsertArgument(stack, s_AttackData.nAttackResult);
    ScriptAPI::InsertArgument(stack, s_AttackData.nAttackNumber);
    for (int k = (MAX_DAMAGE_TYPES - 1); k >= 0; k--)
    {
        ScriptAPI::InsertArgument(stack, s_AttackData.vDamage[k]);
    }
    ScriptAPI::InsertArgument(stack, s_AttackData.oidTarget);

    return stack;
}

NWNX_EXPORT ArgumentStack SetAttackEventData(ArgumentStack&& args)
{
    for (short & k : s_AttackData.vDamage)
    {
        k = (int16_t)args.extract<int32_t>();
    }
    s_AttackData.nAttackResult = args.extract<int32_t>();
    s_AttackData.nSneakAttack = args.extract<int32_t>();

    return {};
}

NWNX_EXPORT ArgumentStack DealDamage(ArgumentStack&& args)
{
    int vDamage[MAX_DAMAGE_TYPES];
    std::bitset<MAX_DAMAGE_TYPES> positive;

    const auto oidSource = args.extract<ObjectID>();
    const auto oidTarget = args.extract<ObjectID>();

    for (int k = 0; k < MAX_DAMAGE_TYPES; k++)
    {
        vDamage[k] = args.extract<int32_t>();
        // need to distinguish between no damage dealt, and damage reduced to 0
        positive[k] = vDamage[k] > 0;
    }
    const auto damagePower = args.extract<int32_t>();
    const auto rangedDamage = args.extract<int32_t>();

    if (auto *pTarget = Utils::AsNWSObject(Utils::GetGameObject(oidTarget)))
    {
        auto *pSource = Utils::AsNWSCreature(Utils::GetGameObject(oidSource));

        // apply damage immunity and resistance
        for (int k = 0; k < MAX_DAMAGE_TYPES; k++)
        {
            if (k == 12) continue; // Skip Base damage type

            if (vDamage[k] > 0)
                vDamage[k] = pTarget->DoDamageImmunity(pSource, vDamage[k], 1 << k, false, false);
            if (vDamage[k] > 0)
                vDamage[k] = pTarget->DoDamageResistance(pSource, vDamage[k], 1 << k, false, false, false, false);
        }

        // apply DR (combine physical damage for this)
        vDamage[12] = vDamage[0] + vDamage[1] + vDamage[2];
        positive[12] = positive[0] || positive[1] || positive[2];
        if (vDamage[12] > 0)
            vDamage[12] = pTarget->DoDamageReduction(pSource, vDamage[12], damagePower, false, false, false);

        auto *pEffect = new CGameEffect(true);
        pEffect->m_nType = 38;
        pEffect->SetCreator(oidSource);
        pEffect->SetNumIntegers(MAX_DAMAGE_TYPES + 7);
        for (int k = 0; k < 3; k++)
            pEffect->SetInteger(k, -1);
        for (int k = 3; k < MAX_DAMAGE_TYPES; k++)
            pEffect->SetInteger(k, positive[k] ? vDamage[k] : -1);
        pEffect->SetInteger(MAX_DAMAGE_TYPES + 1,1000); // Animation Time
        pEffect->SetInteger(MAX_DAMAGE_TYPES + 4, true); // Combat damage
        pEffect->SetInteger(MAX_DAMAGE_TYPES + 5, !!rangedDamage); //Check if ranged (this sets bRangedAttack internally)

        pTarget->ApplyEffect(pEffect, false, true);
    }

    return {};
}
