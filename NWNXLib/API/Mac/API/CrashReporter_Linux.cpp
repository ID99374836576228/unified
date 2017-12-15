#include "CrashReporter_Linux.hpp"
#include "API/Functions.hpp"
#include "Platform/ASLR.hpp"

namespace NWNXLib {

namespace API {

CrashReporter_Linux::CrashReporter_Linux()
{
    __builtin_trap(); // This is an auto-generated stub. You probably shouldn't use it.
}

CrashReporter_Linux::CrashReporter_Linux(const CrashReporter_Linux&)
{
    __builtin_trap(); // This is an auto-generated stub. You probably shouldn't use it.
}

CrashReporter_Linux& CrashReporter_Linux::operator=(const CrashReporter_Linux&)
{
    __builtin_trap(); // This is an auto-generated stub. You probably shouldn't use it.
}

CrashReporter_Linux::CrashReporter_Linux(void* a0)
{
    CrashReporter_Linux__CrashReporter_LinuxCtor__0(this, a0);
}

CrashReporter_Linux::~CrashReporter_Linux()
{
    CrashReporter_Linux__CrashReporter_LinuxDtor__0(this);
}

void CrashReporter_Linux::CanWriteCallstack()
{
    return CrashReporter_Linux__CanWriteCallstack(this);
}

void CrashReporter_Linux::CanWriteMinidump()
{
    return CrashReporter_Linux__CanWriteMinidump(this);
}

void CrashReporter_Linux::CanWriteSystemFiles()
{
    return CrashReporter_Linux__CanWriteSystemFiles(this);
}

void CrashReporter_Linux::InternalCrashHandler(int32_t a0)
{
    return CrashReporter_Linux__InternalCrashHandler(this, a0);
}

void CrashReporter_Linux::WriteCallstack(__sFILE* a0)
{
    return CrashReporter_Linux__WriteCallstack(this, a0);
}

void CrashReporter_Linux::WriteSystemFiles(__sFILE* a0)
{
    return CrashReporter_Linux__WriteSystemFiles(this, a0);
}

void CrashReporter_Linux__CrashReporter_LinuxCtor__0(CrashReporter_Linux* thisPtr, void* a0)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CrashReporter_Linux*, void*);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CrashReporter_Linux__CrashReporter_LinuxCtor__0);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    func(thisPtr, a0);
}

void CrashReporter_Linux__CrashReporter_LinuxDtor__0(CrashReporter_Linux* thisPtr)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CrashReporter_Linux*, int);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CrashReporter_Linux__CrashReporter_LinuxDtor__0);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    func(thisPtr, 2);
}

void CrashReporter_Linux__CanWriteCallstack(CrashReporter_Linux* thisPtr)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CrashReporter_Linux*);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CrashReporter_Linux__CanWriteCallstack);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    func(thisPtr);
}

void CrashReporter_Linux__CanWriteMinidump(CrashReporter_Linux* thisPtr)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CrashReporter_Linux*);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CrashReporter_Linux__CanWriteMinidump);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    func(thisPtr);
}

void CrashReporter_Linux__CanWriteSystemFiles(CrashReporter_Linux* thisPtr)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CrashReporter_Linux*);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CrashReporter_Linux__CanWriteSystemFiles);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    func(thisPtr);
}

void CrashReporter_Linux__InternalCrashHandler(CrashReporter_Linux* thisPtr, int32_t a0)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CrashReporter_Linux*, int32_t);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CrashReporter_Linux__InternalCrashHandler);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    func(thisPtr, a0);
}

void CrashReporter_Linux__WriteCallstack(CrashReporter_Linux* thisPtr, __sFILE* a0)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CrashReporter_Linux*, __sFILE*);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CrashReporter_Linux__WriteCallstack);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    func(thisPtr, a0);
}

void CrashReporter_Linux__WriteSystemFiles(CrashReporter_Linux* thisPtr, __sFILE* a0)
{
    using FuncPtrType = void(__attribute__((cdecl)) *)(CrashReporter_Linux*, __sFILE*);
    uintptr_t address = Platform::ASLR::GetRelocatedAddress(Functions::CrashReporter_Linux__WriteSystemFiles);
    FuncPtrType func = reinterpret_cast<FuncPtrType>(address);
    func(thisPtr, a0);
}

}

}
