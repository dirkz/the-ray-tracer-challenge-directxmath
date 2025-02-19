#pragma once

#include "stdafx.h"

namespace zrt
{

constexpr float Epsilon = 0.0001f;

inline bool IsEqual(float f1, float f2)
{
    return abs(f1 - f2) < Epsilon;
}

inline bool XM_CALLCONV IsEqual(FXMVECTOR v1, FXMVECTOR v2)
{
    using std::isnan;

    XMFLOAT4 components;
    XMStoreFloat4(&components, XMVectorEqual(v1, v2));
    return isnan(components.x) && isnan(components.y) && isnan(components.z) && isnan(components.w);
}

inline XMFLOAT4 XM_CALLCONV Floats(FXMVECTOR v)
{
    XMFLOAT4 floats;
    XMStoreFloat4(&floats, v);

    return floats;
}

} // namespace zrt

namespace DirectX
{

inline bool operator==(const XMFLOAT4 &f1, const XMFLOAT4 &f2)
{
    using zrt::IsEqual;
    return IsEqual(f1.x, f2.x) && IsEqual(f1.y, f2.y) && IsEqual(f1.z, f2.z) && IsEqual(f1.w, f2.w);
}

inline std::ostream &operator<<(std::ostream &os, const XMFLOAT4 &f)
{
    os << "[" << f.x << "," << f.y << "," << f.z << "," << f.w << "]";
    return os;
}

} // namespace DirectX
