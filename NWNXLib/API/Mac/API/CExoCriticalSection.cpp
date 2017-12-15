#include "CExoCriticalSection.hpp"
#include "API/Functions.hpp"
#include "Platform/ASLR.hpp"

#include "CExoCriticalSectionInternal.hpp"

namespace NWNXLib {

namespace API {

CExoCriticalSection::CExoCriticalSection(const CExoCriticalSection&)
{
    __builtin_trap(); // This is an auto-generated stub. You probably shouldn't use it.
}

CExoCriticalSection& CExoCriticalSection::operator=(const CExoCriticalSection&)
{
    __builtin_trap(); // This is an auto-generated stub. You probably shouldn't use it.
}

CExoCriticalSection::CExoCriticalSection()
{
    CExoCriticalSection__CExoCriticalSectionCtor__0(this);
}

CExoCriticalSection::~CExoCriticalSection()
{
    CExoCriticalSection__CExoCriticalSectionDtor__0(this);
}

void CExoCriticalSection::EnterCriticalSection()
{
    return CExoCriticalSection__EnterCriticalSection(this);
}

void CExoCriticalSection::LeaveCriticalSection()
{
    return CExoCriticalSection__LeaveCriticalSection(this);
}

void CExoCriticalSection__CExoCriticalSectionCtor__0(CExoCriticalSection* thisPtr)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CExoCriticalSection*);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CExoCriticalSection__CExoCriticalSectionCtor__0);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    func(thisPtr);
}

void CExoCriticalSection__CExoCriticalSectionDtor__0(CExoCriticalSection* thisPtr)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CExoCriticalSection*, int);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CExoCriticalSection__CExoCriticalSectionDtor__0);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    func(thisPtr, 2);
}

void CExoCriticalSection__EnterCriticalSection(CExoCriticalSection* thisPtr)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CExoCriticalSection*);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CExoCriticalSection__EnterCriticalSection);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    return func(thisPtr);
}

void CExoCriticalSection__LeaveCriticalSection(CExoCriticalSection* thisPtr)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CExoCriticalSection*);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CExoCriticalSection__LeaveCriticalSection);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    return func(thisPtr);
}

}

}
