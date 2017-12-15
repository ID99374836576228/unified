#pragma once

#include <cstdint>

#include "CExoArrayListTemplatedCExoString.hpp"
#include "CExoArrayListTemplatedSSubNetProfilePtr.hpp"
#include "CExoArrayListTemplatedlongunsignedint.hpp"
#include "CExoString.hpp"
#include "CResRef.hpp"
#include "unknown_CExoLinkedListTemplatedunsignedlong.hpp"

namespace NWNXLib {

namespace API {

// Forward class declarations (defined in the source file)
struct C2DA;
struct CCodeBase;
struct CConnectionLib;
struct CExoLinkedListNode;
struct CExoLinkedListTemplatedCNWSClient;
struct CExoLinkedListTemplatedlongunsignedint;
struct CExtendedServerInfo;
struct CFactionManager;
struct CGameObject;
struct CGameObjectArray;
struct CNWPlaceMeshManager;
struct CNWSArea;
struct CNWSAreaOfEffectObject;
struct CNWSClient;
struct CNWSCreature;
struct CNWSDoor;
struct CNWSEncounter;
struct CNWSItem;
struct CNWSMessage;
struct CNWSModule;
struct CNWSPlaceable;
struct CNWSPlayer;
struct CNWSSoundObject;
struct CNWSStore;
struct CNWSTrigger;
struct CNWSWaypoint;
struct CNWVirtualMachineCommands;
struct CNetLayer;
struct CServerAIMaster;
struct CServerInfo;
struct CWorldTimer;

struct CServerExoAppInternal
{
    uint8_t ScratchMessageBuffer[65536];
    int32_t m_bMultiplayerEnabled;
    int32_t m_bGameSpyEnabled;
    int32_t m_bCDResponseReceived;
    CServerInfo* m_pServerInfo;
    int16_t m_nServerMode;
    CNWVirtualMachineCommands* m_pVirtualMachineCommandImplementer;
    CNWSMessage* m_pMessage;
    int32_t m_bForceUpdate;
    uint32_t* m_pPendingAuthorization;
    int32_t m_bTranslatingMasterServer;
    int32_t m_bMasterServerIPCheck;
    CExoArrayListTemplatedlongunsignedint m_lstClientDisconnectPending;
    uint64_t m_nShutdownTimer;
    uint64_t m_nShutdownTimeStamp;
    uint64_t m_nShutdownMaxTimeLocalLogins;
    int32_t m_bReloadModuleWhenEmpty;
    CExoString m_sLastModuleLoadedFilename;
    int32_t m_bLastModuleLoadedWasSaveGame;
    CNetLayer* m_pNetLayer;
    CServerAIMaster* m_pServerAIMaster;
    CWorldTimer* m_pWorldTimer;
    CWorldTimer* m_pTimestopTimer;
    CWorldTimer* m_pPauseTimer;
    CFactionManager* m_pFactionManager;
    CConnectionLib* m_pConnectionLib;
    CCodeBase* m_pCodeBase;
    CGameObjectArray* m_pGameObjArray;
    uint32_t m_oidModule;
    CExoLinkedListTemplatedCNWSClient* m_pNWSPlayerList;
    CExoLinkedListTemplatedCNWSClient* m_pNWSSysAdminList;
    CNWPlaceMeshManager* m_pPlaceMeshManager;
    int32_t m_bDebugMode;
    CExoLinkedListTemplatedlongunsignedint* m_lstPauseExclusionList;
    CExoLinkedListTemplatedlongunsignedint* m_lstTimestopExclusionList;
    uint8_t m_nPauseState;
    int32_t m_bDoingStartNewModule;
    int32_t m_bMoveToModulePending;
    CExoString m_sMoveToModuleString;
    int32_t m_bEndGamePending;
    CExoString m_sEndGameMovie;
    int32_t m_bLoadingModule;
    int32_t m_bImportingChar;
    int32_t m_bAutoSavePending;
    int32_t m_bDisableAutoSave;
    int32_t m_bExportCharacterPending;
    CExoArrayListTemplatedlongunsignedint m_exportPlayerCharacterRequests;
    int32_t m_bNeedSinglePlayerCharacter;
    uint32_t m_nEstimatedSaveSize;
    uint64_t m_nLogHeartbeatTimer;
    uint64_t m_nLogHeartbeatTimeStamp;
    CExoArrayListTemplatedlongunsignedint m_nCharListRequests;
    CExoArrayListTemplatedCExoString m_lstBannedListIP;
    CExoArrayListTemplatedCExoString m_lstBannedListCDKey;
    CExoArrayListTemplatedCExoString m_lstBannedListPlayerName;
    C2DA* m_pOldServerVault2DA;
    C2DA* m_pKnownServerNames2DA;
    uint32_t m_nBannedListsTimeStamp;
    CExoLinkedListNode* m_posPCObject;
    uint64_t m_nAutoSaveTimer;
    CExoArrayListTemplatedSSubNetProfilePtr m_acSubNetProfiles;
    uint64_t m_nTotalSubNetSent;
    uint64_t m_nTotalSubNetRecv;
    uint64_t m_nServerStartupTime;
    int32_t m_nEnableSubNetProfiling;
    int32_t m_bHeartBeatLoggingEnabled;
    int32_t m_bCreatureDeathLoggingEnabled;
    uint32_t m_nClientsRequiredToDisableCPUSleep;
    int32_t m_bStickyCombatModesEnabled;

    // The below are auto generated stubs.
    CServerExoAppInternal(const CServerExoAppInternal&);
    CServerExoAppInternal& operator=(const CServerExoAppInternal&);

    CServerExoAppInternal();
    ~CServerExoAppInternal();
    void AddCDKeyToBannedList(CExoString);
    void AddCharListRequest(uint32_t);
    void AddIPToBannedList(CExoString);
    int32_t AddPendingAuthorization(uint32_t);
    void AddPlayerNameToBannedList(CExoString);
    void AddSubNetProfile(uint32_t, CExoString, CExoString);
    void AddSubNetProfileRecvSize(uint32_t, uint32_t);
    void AddSubNetProfileSendSize(uint32_t, uint32_t);
    void AddToExclusionList(uint32_t, unsigned char);
    int32_t AdmitNetworkAddress(uint32_t, CExoString);
    int32_t AdmitPlayerName(CExoString);
    void CheckMasterServerTranslation();
    int32_t CheckStickyPlayerNameReserved(CExoString, CExoString, CExoString, int32_t);
    void ConnectionLibMainLoop();
    int32_t ContinueMessageProcessing();
    int32_t CopyModuleToCurrentGame(CExoString&, CExoString&, uint16_t);
    int32_t CreateServerVaultLostAndFound();
    void DealWithLoadGameError(uint32_t);
    int32_t EndGame(const CExoString&);
    int32_t ExportAllPlayers();
    int32_t ExportPlayer(CNWSPlayer*);
    CExoLinkedListTemplatedunsignedlong* GetActiveExclusionList();
    unsigned char GetActivePauseState();
    CWorldTimer* GetActiveTimer(uint32_t);
    CNWSArea* GetAreaByGameObjectID(uint32_t);
    CNWSAreaOfEffectObject* GetAreaOfEffectByGameObjectID(uint32_t);
    CExoString GetBannedListString();
    CNWSPlayer* GetClientObjectByObjectId(uint32_t);
    CNWSClient* GetClientObjectByPlayerId(uint32_t, unsigned char);
    CNWSCreature* GetCreatureByGameObjectID(uint32_t);
    int32_t GetDifficultyOption(int32_t);
    CNWSDoor* GetDoorByGameObjectID(uint32_t);
    CNWSEncounter* GetEncounterByGameObjectID(uint32_t);
    void GetExtendedServerInfo(CExtendedServerInfo*);
    int32_t GetFactionOfObject(uint32_t, int32_t*);
    uint32_t GetFirstPCObject();
    CGameObject* GetGameObject(uint32_t);
    int32_t GetIsCDKeyOnBannedList(CExoString);
    int32_t GetIsIPOnBannedList(CExoString);
    int32_t GetIsPlayerNameOnBannedList(CExoString);
    CNWSItem* GetItemByGameObjectID(uint32_t);
    CNWSModule* GetModule();
    CNWSModule* GetModuleByGameObjectID(uint32_t);
    int32_t GetModuleExists(const CExoString&);
    int32_t GetModuleLanguage();
    CExoString GetModuleName();
    uint32_t GetNextPCObject();
    int32_t GetPauseState(unsigned char);
    CNWSPlaceable* GetPlaceableByGameObjectID(uint32_t);
    int32_t GetPlayerAddressData(uint32_t, uint32_t*, unsigned char**, unsigned char**, uint32_t*);
    uint32_t GetPlayerIDByGameObjectID(uint32_t);
    int32_t GetPlayerLanguage(uint32_t);
    CExoString GetPlayerListString();
    CExoString GetPortalListString();
    void GetServerInfoFromIniFile();
    CNWSSoundObject* GetSoundObjectByGameObjectID(uint32_t);
    CNWSStore* GetStoreByGameObjectID(uint32_t);
    CNWSTrigger* GetTriggerByGameObjectID(uint32_t);
    CNWSWaypoint* GetWaypointByGameObjectID(uint32_t);
    void HandleGameSpyToServerMessage(int32_t, void*, int32_t);
    int32_t HandleMessage(uint32_t, unsigned char*, uint32_t, int32_t);
    void HandleOldServerVaultMigration(CExoString, CExoString, CExoString);
    int32_t Initialize();
    void InitializeNetLayer();
    void InitiateModuleForPlayer(void*);
    int32_t IsOnActiveExclusionList(uint32_t);
    int32_t IsOnExclusionList(uint32_t);
    int32_t IsPlayerNameSticky();
    int32_t LoadCharacterFinish(CNWSPlayer*, int32_t, int32_t);
    int32_t LoadCharacterStart(unsigned char, CNWSPlayer*, CResRef, void*, uint32_t);
    int32_t LoadGame(uint32_t, CExoString&, CExoString&, CNWSPlayer*);
    int32_t LoadModule(CExoString, int32_t, CNWSPlayer*);
    int32_t LoadPrimaryPlayer(CNWSPlayer*);
    int32_t MainLoop();
    void MarkUpdateClientsForObject(uint32_t);
    void MovePlayerToArea(void*);
    void OnCDChange();
    void OnExit();
    void OnGainFocus();
    void OnLostFocus();
    void OnVideoChange();
    void PlayerListChange(uint32_t, int32_t, int32_t);
    void PushMessageOverWall(unsigned char*, uint32_t);
    void QuarantineInvalidCharacter(void*, uint32_t);
    void ReadBannedLists();
    void RemoveCDKeyFromBannedList(CExoString);
    void RemoveFromExclusionList(uint32_t, unsigned char);
    void RemoveIPFromBannedList(CExoString);
    void RemovePCFromWorld(CNWSPlayer*);
    int32_t RemovePendingAuthorization(uint32_t);
    void RemovePlayerNameFromBannedList(CExoString);
    void RemoveSubNetProfile(uint32_t);
    void ReprocessExclusionListActions(unsigned char);
    uint32_t ResolvePlayerByFirstName(const CExoString&);
    void RestartNetLayer();
    int32_t RunModule();
    int32_t SaveGame(uint32_t, CExoString&, CExoString&, CNWSPlayer*, int32_t, CExoString&);
    int32_t SendCharacterQuery(CNWSPlayer*);
    int32_t SendEnhancedHeartbeatToMasterServer();
    int32_t SendEnteringStartNewModuleMessage();
    int32_t SendExitingStartNewModuleMessage(int32_t);
    int32_t SendStartStallEvent(uint32_t);
    void SetEstimatedSaveSize(const CExoString&, uint16_t);
    void SetGameSpyReporting(int32_t);
    int32_t SetNetworkAddressBan(uint32_t, CExoString, int32_t);
    void SetPauseState(unsigned char, int32_t);
    void Shutdown(int32_t, int32_t);
    void ShutdownNetLayer();
    void ShutdownServerProfiles();
    void StallEventSaveGame();
    int32_t StartNewModule(CExoString&);
    void StartServices();
    void StartShutdownTimer(uint64_t, uint64_t);
    void StopServices();
    int32_t StorePlayerCharacters();
    int32_t StripColorTokens(CExoString&);
    int32_t Test_Unit_Script_Compile();
    int32_t Test_Unit_Script_Run();
    void TogglePauseState(unsigned char);
    void Uninitialize();
    int32_t UnloadModule();
    void UnlockBiowareModule(CNWSModule*);
    int32_t UpdateAutoSaveTimer();
    void UpdateClientGameObjects(int32_t);
    void UpdateClientGameObjectsForPlayer(CNWSPlayer*, int32_t, uint64_t);
    void UpdateClientsForObject(uint32_t);
    int32_t UpdateLogHeartbeatTimer(uint64_t);
    int32_t UpdateShutdownTimer(uint64_t);
    void UpdateWindowTitle();
    uint32_t ValidateCreateServerCharacter(CNWSPlayer*, void*, uint32_t);
    int32_t ValidatePlayerLogin(void*);
    void VomitServerOptionsToLog();
    void WriteServerInfoToIniFile();
};

void CServerExoAppInternal__CServerExoAppInternalCtor__0(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__CServerExoAppInternalDtor__0(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__AddCDKeyToBannedList(CServerExoAppInternal* thisPtr, CExoString);
void CServerExoAppInternal__AddCharListRequest(CServerExoAppInternal* thisPtr, uint32_t);
void CServerExoAppInternal__AddIPToBannedList(CServerExoAppInternal* thisPtr, CExoString);
int32_t CServerExoAppInternal__AddPendingAuthorization(CServerExoAppInternal* thisPtr, uint32_t);
void CServerExoAppInternal__AddPlayerNameToBannedList(CServerExoAppInternal* thisPtr, CExoString);
void CServerExoAppInternal__AddSubNetProfile(CServerExoAppInternal* thisPtr, uint32_t, CExoString, CExoString);
void CServerExoAppInternal__AddSubNetProfileRecvSize(CServerExoAppInternal* thisPtr, uint32_t, uint32_t);
void CServerExoAppInternal__AddSubNetProfileSendSize(CServerExoAppInternal* thisPtr, uint32_t, uint32_t);
void CServerExoAppInternal__AddToExclusionList(CServerExoAppInternal* thisPtr, uint32_t, unsigned char);
int32_t CServerExoAppInternal__AdmitNetworkAddress(CServerExoAppInternal* thisPtr, uint32_t, CExoString);
int32_t CServerExoAppInternal__AdmitPlayerName(CServerExoAppInternal* thisPtr, CExoString);
void CServerExoAppInternal__CheckMasterServerTranslation(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__CheckStickyPlayerNameReserved(CServerExoAppInternal* thisPtr, CExoString, CExoString, CExoString, int32_t);
void CServerExoAppInternal__ConnectionLibMainLoop(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__ContinueMessageProcessing(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__CopyModuleToCurrentGame(CServerExoAppInternal* thisPtr, CExoString&, CExoString&, uint16_t);
int32_t CServerExoAppInternal__CreateServerVaultLostAndFound(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__DealWithLoadGameError(CServerExoAppInternal* thisPtr, uint32_t);
int32_t CServerExoAppInternal__EndGame(CServerExoAppInternal* thisPtr, const CExoString&);
int32_t CServerExoAppInternal__ExportAllPlayers(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__ExportPlayer(CServerExoAppInternal* thisPtr, CNWSPlayer*);
CExoLinkedListTemplatedunsignedlong* CServerExoAppInternal__GetActiveExclusionList(CServerExoAppInternal* thisPtr);
unsigned char CServerExoAppInternal__GetActivePauseState(CServerExoAppInternal* thisPtr);
CWorldTimer* CServerExoAppInternal__GetActiveTimer(CServerExoAppInternal* thisPtr, uint32_t);
CNWSArea* CServerExoAppInternal__GetAreaByGameObjectID(CServerExoAppInternal* thisPtr, uint32_t);
CNWSAreaOfEffectObject* CServerExoAppInternal__GetAreaOfEffectByGameObjectID(CServerExoAppInternal* thisPtr, uint32_t);
CExoString CServerExoAppInternal__GetBannedListString(CServerExoAppInternal* thisPtr);
CNWSPlayer* CServerExoAppInternal__GetClientObjectByObjectId(CServerExoAppInternal* thisPtr, uint32_t);
CNWSClient* CServerExoAppInternal__GetClientObjectByPlayerId(CServerExoAppInternal* thisPtr, uint32_t, unsigned char);
CNWSCreature* CServerExoAppInternal__GetCreatureByGameObjectID(CServerExoAppInternal* thisPtr, uint32_t);
int32_t CServerExoAppInternal__GetDifficultyOption(CServerExoAppInternal* thisPtr, int32_t);
CNWSDoor* CServerExoAppInternal__GetDoorByGameObjectID(CServerExoAppInternal* thisPtr, uint32_t);
CNWSEncounter* CServerExoAppInternal__GetEncounterByGameObjectID(CServerExoAppInternal* thisPtr, uint32_t);
void CServerExoAppInternal__GetExtendedServerInfo(CServerExoAppInternal* thisPtr, CExtendedServerInfo*);
int32_t CServerExoAppInternal__GetFactionOfObject(CServerExoAppInternal* thisPtr, uint32_t, int32_t*);
uint32_t CServerExoAppInternal__GetFirstPCObject(CServerExoAppInternal* thisPtr);
CGameObject* CServerExoAppInternal__GetGameObject(CServerExoAppInternal* thisPtr, uint32_t);
int32_t CServerExoAppInternal__GetIsCDKeyOnBannedList(CServerExoAppInternal* thisPtr, CExoString);
int32_t CServerExoAppInternal__GetIsIPOnBannedList(CServerExoAppInternal* thisPtr, CExoString);
int32_t CServerExoAppInternal__GetIsPlayerNameOnBannedList(CServerExoAppInternal* thisPtr, CExoString);
CNWSItem* CServerExoAppInternal__GetItemByGameObjectID(CServerExoAppInternal* thisPtr, uint32_t);
CNWSModule* CServerExoAppInternal__GetModule(CServerExoAppInternal* thisPtr);
CNWSModule* CServerExoAppInternal__GetModuleByGameObjectID(CServerExoAppInternal* thisPtr, uint32_t);
int32_t CServerExoAppInternal__GetModuleExists(CServerExoAppInternal* thisPtr, const CExoString&);
int32_t CServerExoAppInternal__GetModuleLanguage(CServerExoAppInternal* thisPtr);
CExoString CServerExoAppInternal__GetModuleName(CServerExoAppInternal* thisPtr);
uint32_t CServerExoAppInternal__GetNextPCObject(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__GetPauseState(CServerExoAppInternal* thisPtr, unsigned char);
CNWSPlaceable* CServerExoAppInternal__GetPlaceableByGameObjectID(CServerExoAppInternal* thisPtr, uint32_t);
int32_t CServerExoAppInternal__GetPlayerAddressData(CServerExoAppInternal* thisPtr, uint32_t, uint32_t*, unsigned char**, unsigned char**, uint32_t*);
uint32_t CServerExoAppInternal__GetPlayerIDByGameObjectID(CServerExoAppInternal* thisPtr, uint32_t);
int32_t CServerExoAppInternal__GetPlayerLanguage(CServerExoAppInternal* thisPtr, uint32_t);
CExoString CServerExoAppInternal__GetPlayerListString(CServerExoAppInternal* thisPtr);
CExoString CServerExoAppInternal__GetPortalListString(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__GetServerInfoFromIniFile(CServerExoAppInternal* thisPtr);
CNWSSoundObject* CServerExoAppInternal__GetSoundObjectByGameObjectID(CServerExoAppInternal* thisPtr, uint32_t);
CNWSStore* CServerExoAppInternal__GetStoreByGameObjectID(CServerExoAppInternal* thisPtr, uint32_t);
CNWSTrigger* CServerExoAppInternal__GetTriggerByGameObjectID(CServerExoAppInternal* thisPtr, uint32_t);
CNWSWaypoint* CServerExoAppInternal__GetWaypointByGameObjectID(CServerExoAppInternal* thisPtr, uint32_t);
void CServerExoAppInternal__HandleGameSpyToServerMessage(CServerExoAppInternal* thisPtr, int32_t, void*, int32_t);
int32_t CServerExoAppInternal__HandleMessage(CServerExoAppInternal* thisPtr, uint32_t, unsigned char*, uint32_t, int32_t);
void CServerExoAppInternal__HandleOldServerVaultMigration(CServerExoAppInternal* thisPtr, CExoString, CExoString, CExoString);
int32_t CServerExoAppInternal__Initialize(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__InitializeNetLayer(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__InitiateModuleForPlayer(CServerExoAppInternal* thisPtr, void*);
int32_t CServerExoAppInternal__IsOnActiveExclusionList(CServerExoAppInternal* thisPtr, uint32_t);
int32_t CServerExoAppInternal__IsOnExclusionList(CServerExoAppInternal* thisPtr, uint32_t);
int32_t CServerExoAppInternal__IsPlayerNameSticky(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__LoadCharacterFinish(CServerExoAppInternal* thisPtr, CNWSPlayer*, int32_t, int32_t);
int32_t CServerExoAppInternal__LoadCharacterStart(CServerExoAppInternal* thisPtr, unsigned char, CNWSPlayer*, CResRef, void*, uint32_t);
int32_t CServerExoAppInternal__LoadGame(CServerExoAppInternal* thisPtr, uint32_t, CExoString&, CExoString&, CNWSPlayer*);
int32_t CServerExoAppInternal__LoadModule(CServerExoAppInternal* thisPtr, CExoString, int32_t, CNWSPlayer*);
int32_t CServerExoAppInternal__LoadPrimaryPlayer(CServerExoAppInternal* thisPtr, CNWSPlayer*);
int32_t CServerExoAppInternal__MainLoop(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__MarkUpdateClientsForObject(CServerExoAppInternal* thisPtr, uint32_t);
void CServerExoAppInternal__MovePlayerToArea(CServerExoAppInternal* thisPtr, void*);
void CServerExoAppInternal__OnCDChange(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__OnExit(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__OnGainFocus(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__OnLostFocus(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__OnVideoChange(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__PlayerListChange(CServerExoAppInternal* thisPtr, uint32_t, int32_t, int32_t);
void CServerExoAppInternal__PushMessageOverWall(CServerExoAppInternal* thisPtr, unsigned char*, uint32_t);
void CServerExoAppInternal__QuarantineInvalidCharacter(CServerExoAppInternal* thisPtr, void*, uint32_t);
void CServerExoAppInternal__ReadBannedLists(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__RemoveCDKeyFromBannedList(CServerExoAppInternal* thisPtr, CExoString);
void CServerExoAppInternal__RemoveFromExclusionList(CServerExoAppInternal* thisPtr, uint32_t, unsigned char);
void CServerExoAppInternal__RemoveIPFromBannedList(CServerExoAppInternal* thisPtr, CExoString);
void CServerExoAppInternal__RemovePCFromWorld(CServerExoAppInternal* thisPtr, CNWSPlayer*);
int32_t CServerExoAppInternal__RemovePendingAuthorization(CServerExoAppInternal* thisPtr, uint32_t);
void CServerExoAppInternal__RemovePlayerNameFromBannedList(CServerExoAppInternal* thisPtr, CExoString);
void CServerExoAppInternal__RemoveSubNetProfile(CServerExoAppInternal* thisPtr, uint32_t);
void CServerExoAppInternal__ReprocessExclusionListActions(CServerExoAppInternal* thisPtr, unsigned char);
uint32_t CServerExoAppInternal__ResolvePlayerByFirstName(CServerExoAppInternal* thisPtr, const CExoString&);
void CServerExoAppInternal__RestartNetLayer(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__RunModule(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__SaveGame(CServerExoAppInternal* thisPtr, uint32_t, CExoString&, CExoString&, CNWSPlayer*, int32_t, CExoString&);
int32_t CServerExoAppInternal__SendCharacterQuery(CServerExoAppInternal* thisPtr, CNWSPlayer*);
int32_t CServerExoAppInternal__SendEnhancedHeartbeatToMasterServer(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__SendEnteringStartNewModuleMessage(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__SendExitingStartNewModuleMessage(CServerExoAppInternal* thisPtr, int32_t);
int32_t CServerExoAppInternal__SendStartStallEvent(CServerExoAppInternal* thisPtr, uint32_t);
void CServerExoAppInternal__SetEstimatedSaveSize(CServerExoAppInternal* thisPtr, const CExoString&, uint16_t);
void CServerExoAppInternal__SetGameSpyReporting(CServerExoAppInternal* thisPtr, int32_t);
int32_t CServerExoAppInternal__SetNetworkAddressBan(CServerExoAppInternal* thisPtr, uint32_t, CExoString, int32_t);
void CServerExoAppInternal__SetPauseState(CServerExoAppInternal* thisPtr, unsigned char, int32_t);
void CServerExoAppInternal__Shutdown(CServerExoAppInternal* thisPtr, int32_t, int32_t);
void CServerExoAppInternal__ShutdownNetLayer(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__ShutdownServerProfiles(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__StallEventSaveGame(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__StartNewModule(CServerExoAppInternal* thisPtr, CExoString&);
void CServerExoAppInternal__StartServices(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__StartShutdownTimer(CServerExoAppInternal* thisPtr, uint64_t, uint64_t);
void CServerExoAppInternal__StopServices(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__StorePlayerCharacters(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__StripColorTokens(CServerExoAppInternal* thisPtr, CExoString&);
int32_t CServerExoAppInternal__Test_Unit_Script_Compile(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__Test_Unit_Script_Run(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__TogglePauseState(CServerExoAppInternal* thisPtr, unsigned char);
void CServerExoAppInternal__Uninitialize(CServerExoAppInternal* thisPtr);
int32_t CServerExoAppInternal__UnloadModule(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__UnlockBiowareModule(CServerExoAppInternal* thisPtr, CNWSModule*);
int32_t CServerExoAppInternal__UpdateAutoSaveTimer(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__UpdateClientGameObjects(CServerExoAppInternal* thisPtr, int32_t);
void CServerExoAppInternal__UpdateClientGameObjectsForPlayer(CServerExoAppInternal* thisPtr, CNWSPlayer*, int32_t, uint64_t);
void CServerExoAppInternal__UpdateClientsForObject(CServerExoAppInternal* thisPtr, uint32_t);
int32_t CServerExoAppInternal__UpdateLogHeartbeatTimer(CServerExoAppInternal* thisPtr, uint64_t);
int32_t CServerExoAppInternal__UpdateShutdownTimer(CServerExoAppInternal* thisPtr, uint64_t);
void CServerExoAppInternal__UpdateWindowTitle(CServerExoAppInternal* thisPtr);
uint32_t CServerExoAppInternal__ValidateCreateServerCharacter(CServerExoAppInternal* thisPtr, CNWSPlayer*, void*, uint32_t);
int32_t CServerExoAppInternal__ValidatePlayerLogin(CServerExoAppInternal* thisPtr, void*);
void CServerExoAppInternal__VomitServerOptionsToLog(CServerExoAppInternal* thisPtr);
void CServerExoAppInternal__WriteServerInfoToIniFile(CServerExoAppInternal* thisPtr);

}

}
