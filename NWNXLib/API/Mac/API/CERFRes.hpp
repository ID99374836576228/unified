#pragma once

#include <cstdint>

#include "CExoFile.hpp"

namespace NWNXLib {

namespace API {

struct CERFRes
{
    uint32_t m_nOffset;
    uint32_t m_nSize;
    uint8_t* m_pData;

    // The below are auto generated stubs.
    CERFRes(const CERFRes&);
    CERFRes& operator=(const CERFRes&);

    CERFRes();
    ~CERFRes();
    int32_t Read();
    int32_t Reset();
    int32_t Write(CExoFile&, uint32_t);
};

void CERFRes__CERFResCtor__0(CERFRes* thisPtr);
void CERFRes__CERFResDtor__0(CERFRes* thisPtr);
int32_t CERFRes__Read(CERFRes* thisPtr);
int32_t CERFRes__Reset(CERFRes* thisPtr);
int32_t CERFRes__Write(CERFRes* thisPtr, CExoFile&, uint32_t);

}

}
