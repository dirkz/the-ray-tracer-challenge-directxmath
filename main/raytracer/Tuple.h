#pragma once

#include "stdafx.h"

namespace zrt
{

constexpr float AllBitsFloat = 0xFFFFFFFF;

inline XMVECTOR XM_CALLCONV Tuple(float x, float y, float z, float w)
{
    return XMVectorSet(x, y, z, w);
}

inline XMVECTOR XM_CALLCONV Vector(float x, float y, float z)
{
    return Tuple(x, y, z, 0);
}

inline XMVECTOR XM_CALLCONV Point(float x, float y, float z)
{
    return Tuple(x, y, z, 1);
}

inline bool XM_CALLCONV IsPoint(FXMVECTOR v)
{
    return XMVectorGetW(v) == 1.f;
}

inline bool XM_CALLCONV IsVector(FXMVECTOR v)
{
    return XMVectorGetW(v) == 0.f;
}

inline bool XM_CALLCONV IsEqual(FXMVECTOR v1, FXMVECTOR v2)
{
    XMFLOAT4 components;
    XMStoreFloat4(&components, XMVectorEqual(v1, v2));
    return components.x == AllBitsFloat && components.y == AllBitsFloat &&
           components.z == AllBitsFloat && components.w == AllBitsFloat;
}

} // namespace zrt
