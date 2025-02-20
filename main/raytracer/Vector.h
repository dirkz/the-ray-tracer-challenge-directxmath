#pragma once

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

inline XMVECTOR XM_CALLCONV Reflect(FXMVECTOR v, FXMVECTOR n)
{
    return XMVector4Reflect(v, n);
}

inline XMVECTOR XM_CALLCONV Color(float r, float g, float b)
{
    return Tuple(r, g, b, 1);
}

} // namespace zrt

