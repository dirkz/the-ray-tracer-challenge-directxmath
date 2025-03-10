#include <gtest/gtest.h>

#include "TestUtil.h"

#include "Cone.h"
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

struct ConeCapData
{
    ConeCapData(FXMVECTOR origin, FXMVECTOR direction, size_t count) : m_count{count}
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

    inline size_t Count() const
    {
        return m_count;
    }

  private:
    XMFLOAT4 m_origin;
    XMFLOAT4 m_direction;
    size_t m_count;
};

struct ConeNormalData
{
    ConeNormalData(FXMVECTOR point, FXMVECTOR normal)
    {
        XMStoreFloat4(&m_point, point);
        XMStoreFloat4(&m_normal, normal);
    }

    inline XMVECTOR XM_CALLCONV Point() const
    {
        return XMLoadFloat4(&m_point);
    }

    inline XMVECTOR XM_CALLCONV Normal() const
    {
        return XMLoadFloat4(&m_normal);
    }

  private:
    XMFLOAT4 m_point;
    XMFLOAT4 m_normal;
};

struct ConeRayHits : public testing::TestWithParam<ConeRayHitsData>
{
};

struct ConeCap : public testing::TestWithParam<ConeCapData>
{
};

struct ConeNormal : public testing::TestWithParam<ConeNormalData>
{
};

TEST_P(ConeRayHits, RayHits)
{
    ConeRayHitsData param = GetParam();

    Cone cone{};

    XMVECTOR direction = XMVector3Normalize(param.Direction());
    Ray r{param.Origin(), direction};

    auto xs = cone.LocalIntersect(r);

    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].T(), param.T0());
    EXPECT_FLOAT_EQ(xs[1].T(), param.T1());
}

INSTANTIATE_TEST_CASE_P(
    ConeTest, ConeRayHits,
    testing::Values(ConeRayHitsData{Point(0, 0, -5), Vector(0, 0, 1), 5, 5},
                    ConeRayHitsData{Point(0, 0, -5), Vector(1, 1, 1), 8.6602545f, 8.6602545f},
                    ConeRayHitsData{Point(1, 1, -5), Vector(-0.5, -1, 1), 4.5500546f, 49.44994f}));

TEST(ConeTest, IntersectingConeWithRayParallelToOneOfItsHalves)
{
    Cone shape{};
    XMVECTOR direction = XMVector3Normalize(Vector(0, 1, 1));
    Ray r{Point(0, 0, -1), direction};
    auto xs = shape.LocalIntersect(r);
    ASSERT_EQ(xs.size(), 1);
    EXPECT_FLOAT_EQ(xs[0].T(), 0.35355338f);
}

TEST_P(ConeCap, ConeCappedRay)
{
    ConeCapData param = GetParam();

    Material m{};
    Cone shape{XMMatrixIdentity(), m, -0.5f, 0.5f, true};

    XMVECTOR direction = XMVector3Normalize(param.Direction());
    Ray r{param.Origin(), direction};

    auto xs = shape.LocalIntersect(r);
    EXPECT_EQ(xs.size(), param.Count());
}

INSTANTIATE_TEST_CASE_P(ConeTest, ConeCap,
                        testing::Values(ConeCapData{Point(0, 0, -5), Vector(0, 1, 0), 0},
                                        ConeCapData{Point(0, 0, -0.25f), Vector(0, 1, 1), 2},
                                        ConeCapData{Point(0, 0, -0.25f), Vector(0, 1, 0), 4}));

TEST_P(ConeNormal, ConeNormalVector)
{
    ConeNormalData param = GetParam();

    Cone shape{};
    auto n = shape.LocalNormal(param.Point());
    EXPECT_EQ(Floats(param.Normal()), Floats(n));
}

INSTANTIATE_TEST_CASE_P(ConeTest, ConeNormal,
                        testing::Values(ConeNormalData{Point(0, 0, 0), Vector(0, 0, 0)},
                                        ConeNormalData{Point(1, 1, 1),
                                                       Vector(1, -std::sqrt(2.f), 1)},
                                        ConeNormalData{Point(-1, -1, 0), Vector(-1, 1, 0)}));

} // namespace zrt