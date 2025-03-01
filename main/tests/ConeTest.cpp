#include <gtest/gtest.h>

#include "Cone.h"
#include "TestUtil.h"
#include "Vector.h"

namespace zrt
{

struct ConeRayHitsData
{
    ConeRayHitsData(FXMVECTOR origin, FXMVECTOR direction, float t0, float t1) : m_t0{t0}, m_t1{t1}
    {
        XMStoreFloat4(&m_origin, origin);
        XMStoreFloat4(&m_direction, direction);
    }

    inline XMVECTOR XM_CALLCONV Origin() const
    {
        return XMLoadFloat4(&m_origin);
    }

    inline XMVECTOR XM_CALLCONV Direction() const
    {
        return XMLoadFloat4(&m_direction);
    }

    inline float T0() const
    {
        return m_t0;
    }

    inline float T1() const
    {
        return m_t1;
    }

  private:
    XMFLOAT4 m_origin;
    XMFLOAT4 m_direction;
    float m_t0;
    float m_t1;
};

struct ConeRayHits : public testing::TestWithParam<ConeRayHitsData>
{
};

TEST_P(ConeRayHits, RayHits)
{
    ConeRayHitsData param = GetParam();

    Cone cone{};

    XMVECTOR direction = XMVector4Normalize(param.Direction());
    Ray r{param.Origin(), direction};

    auto xs = cone.LocalIntersect(r);

    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].T(), param.T0());
    EXPECT_FLOAT_EQ(xs[1].T(), param.T1());
}

INSTANTIATE_TEST_CASE_P(
    ConeTest, ConeRayHits,
    testing::Values(ConeRayHitsData{Point(0, 0, -5), Vector(0, 0, 1), 5, 5},
                    ConeRayHitsData{Point(0, 0, -5), Vector(1, 1, 1), 8.66025f, 8.66025f},
                    ConeRayHitsData{Point(1, 1, -5), Vector(-0.5, -1, 1), 4.55006f, 49.44994f}));

TEST(ConeTest, IntersectingConeWithRayParallelToOneOfItsHalves)
{
    Cone shape{};
    XMVECTOR direction = XMVector4Normalize(Vector(0, 1, 1));
    Ray r{Point(0, 0, -1), direction};
    auto xs = shape.LocalIntersect(r);
    ASSERT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].T(), 0.35355f);
}

} // namespace zrt