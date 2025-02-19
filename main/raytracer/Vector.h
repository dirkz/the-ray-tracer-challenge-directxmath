#pragma once

#include "stdafx.h"

#include "Floats.h"

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

inline XMVECTOR XM_CALLCONV Point(float all)
{
    return Tuple(all, all, all, 1);
}

inline XMVECTOR XM_CALLCONV PointToVector(FXMVECTOR p)
{
    XMFLOAT4 floats;
    XMStoreFloat4(&floats, p);
    floats.w = 0;
    return XMLoadFloat4(&floats);
}

inline XMVECTOR XM_CALLCONV VectorToPoint(FXMVECTOR p)
{
    XMFLOAT4 floats;
    XMStoreFloat4(&floats, p);
    floats.w = 1;
    return XMLoadFloat4(&floats);
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

inline XMFLOAT4 XM_CALLCONV Floats(FXMVECTOR v)
{
    XMFLOAT4 floats;
    XMStoreFloat4(&floats, v);

    return floats;
}

inline XMVECTOR XM_CALLCONV Reflect(FXMVECTOR v, FXMVECTOR n)
{
    return XMVector4Reflect(v, n);
}

inline XMVECTOR XM_CALLCONV Color(float r, float g, float b)
{
    return Tuple(r, g, b, 1);
}

} // namespace zrt

namespace DirectX
{

inline bool operator==(const XMFLOAT4 &f1, const XMFLOAT4 &f2)
{
    using zrt::IsEqual;
    return IsEqual(f1.x, f2.x) && IsEqual(f1.y, f2.y) && IsEqual(f1.z, f2.z) && IsEqual(f1.w, f2.w);
}

std::ostream &operator<<(std::ostream &os, const XMFLOAT4 &f);

} // namespace DirectX
