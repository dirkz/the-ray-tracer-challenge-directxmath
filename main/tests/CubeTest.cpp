#include <gtest/gtest.h>

#include "TestUtil.h"

#include "Cube.h"
#include "Vector.h"

namespace zrt
{

struct CubeRayHitData
{
    CubeRayHitData(FXMVECTOR origin, FXMVECTOR direction, float t1, float t2) : m_t1{t1}, m_t2{t2}
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

struct CubeRayMissData
{
    CubeRayMissData(FXMVECTOR origin, FXMVECTOR direction)
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

struct CubeNormalData
{
    CubeNormalData(FXMVECTOR point, FXMVECTOR normal)
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

struct CubeRayHit : public testing::TestWithParam<CubeRayHitData>
{
};

struct CubeRayMiss : public testing::TestWithParam<CubeRayMissData>
{
};

struct CubeNormal : public testing::TestWithParam<CubeNormalData>
{
};

TEST_P(CubeRayHit, RayHits)
{
    CubeRayHitData param = GetParam();

    Cube c{};
    Ray r{param.Origin(), param.Direction()};

    auto xs = c.Intersect(r);

    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].T(), param.T1());
    EXPECT_FLOAT_EQ(xs[1].T(), param.T2());
}

TEST_P(CubeRayMiss, RayMisses)
{
    CubeRayMissData param = GetParam();

    Cube c{};
    Ray r{param.Origin(), param.Direction()};

    auto xs = c.Intersect(r);

    EXPECT_TRUE(xs.empty());
}

TEST_P(CubeNormal, Normals)
{
    CubeNormalData param = GetParam();

    Cube c{};

    auto p = param.Point();
    auto normal = c.Normal(p);
    auto n = param.Normal();

    EXPECT_EQ(Floats(n), Floats(normal));
}

INSTANTIATE_TEST_CASE_P(CubeTest, CubeRayHit,
                        testing::Values(CubeRayHitData{Point(5, 0.5f, 0), Vector(-1, 0, 0), 4, 6},
                                        CubeRayHitData{Point(-5, 0.5f, 0), Vector(1, 0, 0), 4, 6},
                                        CubeRayHitData{Point(0.5f, 5, 0), Vector(0, -1, 0), 4, 6},
                                        CubeRayHitData{Point(0.5, -5, 0), Vector(0, 1, 0), 4, 6},
                                        CubeRayHitData{Point(0.5f, 0, 5), Vector(0, 0, -1), 4, 6},
                                        CubeRayHitData{Point(0.5, 0, -5), Vector(0, 0, 1), 4, 6},
                                        CubeRayHitData{Point(0, 0.5, 0), Vector(0, 0, 1), -1, 1}));

INSTANTIATE_TEST_CASE_P(
    CubeTest, CubeRayMiss,
    testing::Values(CubeRayMissData{Point(-2, 0, 0), Vector(0.2673f, 0.5345f, 0.8018f)},
                    CubeRayMissData{Point(0, -2, 0), Vector(0.8018f, 0.2673f, 0.5345f)},
                    CubeRayMissData{Point(0, 0, -2), Vector(0.5345f, 0.8018f, 0.2673f)},
                    CubeRayMissData{Point(2, 0, 2), Vector(0, 0, -1)},
                    CubeRayMissData{Point(0, 2, 2), Vector(0, -1, 0)},
                    CubeRayMissData{Point(2, 2, 0), Vector(-1, 0, 0)}));

INSTANTIATE_TEST_CASE_P(CubeTest, CubeNormal,
                        testing::Values(CubeNormalData{Point(1, 0.5f, -0.8f), Vector(1, 0, 0)},
                                        CubeNormalData{Point(-1, -0.2f, 0.9f), Vector(-1, 0, 0)},
                                        CubeNormalData{Point(-0.4f, 1, -0.1f), Vector(0, 1, 0)},
                                        CubeNormalData{Point(0.3f, -1, -0.7f), Vector(0, -1, 0)},
                                        CubeNormalData{Point(-0.6f, 0.3f, 1), Vector(0, 0, 1)},
                                        CubeNormalData{Point(0.4f, 0.4f, -1), Vector(0, 0, -1)},
                                        CubeNormalData{Point(1, 1, 1), Vector(1, 0, 0)},
                                        CubeNormalData{Point(-1, -1, -1), Vector(-1, 0, 0)}));

} // namespace zrt