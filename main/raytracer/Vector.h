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
    using std::isnan;

    XMFLOAT4 components;
    XMStoreFloat4(&components, XMVectorEqual(v1, v2));
    return isnan(components.x) && isnan(components.y) && isnan(components.z) && isnan(components.w);
}

inline float XM_CALLCONV DotProduct(FXMVECTOR v1, FXMVECTOR v2)
{
    XMVECTOR v = XMVector4Dot(v1, v2);
    XMFLOAT4 floats;
    XMStoreFloat4(&floats, v);

#ifdef _DEBUG
    if (!std::isnan(floats.x))
    {
        assert(floats.x == floats.y);
        assert(floats.y == floats.z);
        assert(floats.z == floats.w);
    }
#endif

    return floats.x;
}

} // namespace zrt

namespace DirectX
{

std::ostream &XM_CALLCONV operator<<(std::ostream &os, FXMVECTOR v);
void PrintTo(const XMVECTOR &v, ::std::ostream *os);

}
