#pragma once

#include "stdafx.h"

#include "Intersectable.h"
#include "Material.h"
#include "Matrix.h"
#include "Sphere.h"
#include "World.h"

namespace zrt
{

constexpr float WorldMaterial1DefaultAmbient = 0.1f;
constexpr float WorldMaterial1DefaultDiffuse = 0.7f;
constexpr float WorldMaterial1DefaultSpecular = 0.2f;

const Material M1 = Material{Color(0.8f, 1, 0.6f), WorldMaterial1DefaultAmbient,
                             WorldMaterial1DefaultDiffuse, WorldMaterial1DefaultSpecular};
const PointLight PL{Point(-10, 10, -10), Color(1, 1, 1)};

inline World DefaultWorld(const PointLight &light = PL, const Material &m1 = M1,
                          const Material &m2 = Material{})
{
    Intersectable *s1 = new Sphere{XMMatrixIdentity(), m1};
    Intersectable *s2 = new Sphere{Scaling(0.5f, 0.5f, 0.5f), m2};

    World w{light, {s1, s2}};

    EXPECT_EQ(w.Lights().size(), 1);
    PointLight light2 = w.Lights()[0];
    EXPECT_EQ(light2, light);

    auto itS1 = std::find(w.Objects().begin(), w.Objects().end(), s1);
    auto itS2 = std::find(w.Objects().begin(), w.Objects().end(), s2);

    EXPECT_TRUE(itS1 != w.Objects().end());

    return w;
}

/// <summary>
/// Good-enough epsilon specifically (and only) for the tests.
/// </summary>
constexpr float Epsilon = 0.0001f;

/// <summary>
/// This by no means a good way to compare float values, but good enough for these specific tests.
/// <a
/// href="https://www.boost.org/doc/libs/1_87_0/libs/math/doc/html/math_toolkit/float_comparison.html">
/// See here for real tooling
/// </a> (just to give an example).
/// </summary>
/// <param name="f1"></param>
/// <param name="f2"></param>
/// <returns></returns>
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
