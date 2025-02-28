#include "stdafx.h"

#include <gtest/gtest.h>

#include "Cube.h"
#include "TestUtil.h"
#include "Vector.h"

namespace zrt
{

struct RayHitData
{
    RayHitData(FXMVECTOR origin, FXMVECTOR direction, float t1, float t2) : m_t1{t1}, m_t2{t2}
    {
        XMStoreFloat4(&m_origin, origin);
        XMStoreFloat4(&m_direction, direction);
    };

    XMVECTOR XM_CALLCONV Origin() const
    {
        return XMLoadFloat4(&m_origin);
    }

    XMVECTOR XM_CALLCONV Direction() const
    {
        return XMLoadFloat4(&m_direction);
    }

    float T1() const
    {
        return m_t1;
    }

    float T2() const
    {
        return m_t2;
    }

  private:
    XMFLOAT4 m_origin;
    XMFLOAT4 m_direction;
    float m_t1;
    float m_t2;
};

struct RayMissData
{
    RayMissData(FXMVECTOR origin, FXMVECTOR direction)
    {
        XMStoreFloat4(&m_origin, origin);
        XMStoreFloat4(&m_direction, direction);
    };

    XMVECTOR XM_CALLCONV Origin() const
    {
        return XMLoadFloat4(&m_origin);
    }

    XMVECTOR XM_CALLCONV Direction() const
    {
        return XMLoadFloat4(&m_direction);
    }

  private:
    XMFLOAT4 m_origin;
    XMFLOAT4 m_direction;
};

struct NormalData
{
    NormalData(FXMVECTOR point, FXMVECTOR normal)
    {
        XMStoreFloat4(&m_point, point);
        XMStoreFloat4(&m_normal, normal);
    }

    XMVECTOR XM_CALLCONV Point() const
    {
        return XMLoadFloat4(&m_point);
    }

    XMVECTOR XM_CALLCONV Normal() const
    {
        return XMLoadFloat4(&m_normal);
    }

  private:
    XMFLOAT4 m_point;
    XMFLOAT4 m_normal;
};

struct RayHit : public testing::TestWithParam<RayHitData>
{
};

struct RayMiss : public testing::TestWithParam<RayMissData>
{
};

struct Normal : public testing::TestWithParam<NormalData>
{
};

TEST_P(RayHit, RayHits)
{
    RayHitData param = GetParam();

    Cube c{};
    Ray r{param.Origin(), param.Direction()};

    auto xs = c.Intersect(r);

    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].T(), param.T1());
    EXPECT_FLOAT_EQ(xs[1].T(), param.T2());
}

TEST_P(RayMiss, RayMisses)
{
    RayMissData param = GetParam();

    Cube c{};
    Ray r{param.Origin(), param.Direction()};

    auto xs = c.Intersect(r);

    EXPECT_EQ(xs.size(), 0);
}

TEST_P(Normal, Normals)
{
    NormalData param = GetParam();

    Cube c{};

    auto p = param.Point();
    auto normal = c.Normal(p);
    auto n = param.Normal();

    EXPECT_EQ(Floats(n), Floats(normal));
}

INSTANTIATE_TEST_CASE_P(CubeTest, RayHit,
                        testing::Values(RayHitData{Point(5, 0.5f, 0), Vector(-1, 0, 0), 4, 6},
                                        RayHitData{Point(-5, 0.5f, 0), Vector(1, 0, 0), 4, 6},
                                        RayHitData{Point(0.5f, 5, 0), Vector(0, -1, 0), 4, 6},
                                        RayHitData{Point(0.5, -5, 0), Vector(0, 1, 0), 4, 6},
                                        RayHitData{Point(0.5f, 0, 5), Vector(0, 0, -1), 4, 6},
                                        RayHitData{Point(0.5, 0, -5), Vector(0, 0, 1), 4, 6},
                                        RayHitData{Point(0, 0.5, 0), Vector(0, 0, 1), -1, 1}));

INSTANTIATE_TEST_CASE_P(
    CubeTest, RayMiss,
    testing::Values(RayMissData{Point(-2, 0, 0), Vector(0.2673f, 0.5345f, 0.8018f)},
                    RayMissData{Point(0, -2, 0), Vector(0.8018f, 0.2673f, 0.5345f)},
                    RayMissData{Point(0, 0, -2), Vector(0.5345f, 0.8018f, 0.2673f)},
                    RayMissData{Point(2, 0, 2), Vector(0, 0, -1)},
                    RayMissData{Point(0, 2, 2), Vector(0, -1, 0)},
                    RayMissData{Point(2, 2, 0), Vector(-1, 0, 0)}));

INSTANTIATE_TEST_CASE_P(CubeTest, Normal,
                        testing::Values(NormalData{Point(1, 0.5f, -0.8f), Vector(1, 0, 0)},
                                        NormalData{Point(-1, -0.2f, 0.9f), Vector(-1, 0, 0)},
                                        NormalData{Point(-0.4f, 1, -0.1f), Vector(0, 1, 0)},
                                        NormalData{Point(0.3f, -1, -0.7f), Vector(0, -1, 0)},
                                        NormalData{Point(-0.6f, 0.3f, 1), Vector(0, 0, 1)},
                                        NormalData{Point(0.4f, 0.4f, -1), Vector(0, 0, -1)},
                                        NormalData{Point(1, 1, 1), Vector(1, 0, 0)},
                                        NormalData{Point(-1, -1, -1), Vector(-1, 0, 0)}));

} // namespace zrt