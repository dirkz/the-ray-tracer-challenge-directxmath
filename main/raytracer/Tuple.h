#pragma once

#include "stdafx.h"

namespace zrt
{

inline XMVECTOR XM_CALLCONV Tuple(float x, float y, float z, float w)
{
    return XMVectorSet(x, y, z, w);
}

inline XMVECTOR XM_CALLCONV Vector(float x, float y, float z)
{
    return Tuple(x, y, z, 0);
}

inline XMVECTOR XM_CALLCONV Tuple(float x, float y, float z)
{
    return Tuple(x, y, z, 1);
}

} // namespace zrt
