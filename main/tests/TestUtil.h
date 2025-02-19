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

inline XMFLOAT4X4 XM_CALLCONV Floats(FXMMATRIX m)
{
    XMFLOAT4X4 floats;
    XMStoreFloat4x4(&floats, m);

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

inline bool operator==(const XMFLOAT4X4 &m1, const XMFLOAT4X4 &m2)
{
    using zrt::IsEqual;

    for (auto r = 0; r < 3; ++r)
    {
        for (auto c = 0; c < 3; ++c)
        {
            float f1 = m1(r, c);
            float f2 = m2(r, c);
            if (!IsEqual(f1, f2))
            {
                return false;
            }
        }
    }

    return true;
}

inline std::ostream &operator<<(std::ostream &os, const XMFLOAT4 &f)
{
    os << "[" << f.x << "," << f.y << "," << f.z << "," << f.w << "]";
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const XMFLOAT4X4 &m)
{
	os << "\n";
    for (auto r = 0; r < 3; ++r)
    {
        for (auto c = 0; c < 3; ++c)
        {
            if (c > 0)
            {
                os << ",";
            }
            float f = m(r, c);
            os << f;
        }
        if (r < 3)
        {
            os << "\n";
        }
    }

    return os;
}

} // namespace DirectX
