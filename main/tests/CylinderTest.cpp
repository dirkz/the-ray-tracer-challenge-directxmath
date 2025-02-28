#include <gtest/gtest.h>

#include "Cube.h"
#include "Cylinder.h"
#include "TestUtil.h"
#include "Vector.h"

namespace zrt
{

struct CylinderRayMissData
{
    CylinderRayMissData(FXMVECTOR origin, FXMVECTOR direction)
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

  private:
    XMFLOAT4 m_origin;
    XMFLOAT4 m_direction;
};

struct CylinderRayHitsData
{
    CylinderRayHitsData(FXMVECTOR origin, FXMVECTOR direction, float t0, float t1)
        : m_t0{t0}, m_t1{t1}
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

struct CylinderNormalData
{
    CylinderNormalData(FXMVECTOR point, FXMVECTOR normal)
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

struct CylinderConstrainedOrCappedData
{
    CylinderConstrainedOrCappedData(FXMVECTOR point, FXMVECTOR direction, size_t count)
        : m_count{count}
    {
        XMStoreFloat4(&m_point, point);
        XMStoreFloat4(&m_direction, direction);
    }

    inline XMVECTOR XM_CALLCONV Point() const
    {
        return XMLoadFloat4(&m_point);
    }

    inline XMVECTOR XM_CALLCONV Direction() const
    {
        return XMLoadFloat4(&m_direction);
    }

    inline float Count() const
    {
        return m_count;
    }

  private:
    XMFLOAT4 m_point;
    XMFLOAT4 m_direction;
    size_t m_count;
};

struct CylinderRayMiss : public testing::TestWithParam<CylinderRayMissData>
{
};

struct CylinderRayHits : public testing::TestWithParam<CylinderRayHitsData>
{
};

struct CylinderNormal : public testing::TestWithParam<CylinderNormalData>
{
};

struct CylinderConstrained : public testing::TestWithParam<CylinderConstrainedOrCappedData>
{
};

struct CylinderCapped : public testing::TestWithParam<CylinderConstrainedOrCappedData>
{
};

TEST_P(CylinderRayMiss, RayMisses)
{
    CylinderRayMissData param = GetParam();
    Cylinder cyl{};
    Ray r{param.Origin(), param.Direction()};
    auto xs = cyl.Intersect(r);
    EXPECT_TRUE(xs.empty());
}

TEST_P(CylinderRayHits, RayHits)
{
    CylinderRayHitsData param = GetParam();

    Cylinder cyl{};

    XMVECTOR direction = XMVector4Normalize(param.Direction());
    Ray r{param.Origin(), direction};

    auto xs = cyl.LocalIntersect(r);

    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].T(), param.T0());
    EXPECT_FLOAT_EQ(xs[1].T(), param.T1());
}

TEST_P(CylinderNormal, Normal)
{
    CylinderNormalData param = GetParam();
    XMVECTOR point = param.Point();
    XMVECTOR expectedNormal = param.Normal();

    Cylinder cyl{};
    XMVECTOR normal = cyl.Normal(point);

    EXPECT_EQ(Floats(expectedNormal), Floats(normal));
}

TEST_P(CylinderConstrained, ConstrainedIntersections)
{
}

TEST_P(CylinderCapped, CappedIntersections)
{
}

INSTANTIATE_TEST_CASE_P(CylinderTest, CylinderRayMiss,
                        testing::Values(CylinderRayMissData{Point(1, 0, 0), Vector(0, 1, 0)},
                                        CylinderRayMissData{Point(0, 0, 0), Vector(0, 1, 0)},
                                        CylinderRayMissData{Point(0, 0, -5), Vector(1, 1, 1)}));

INSTANTIATE_TEST_CASE_P(CylinderTest, CylinderRayHits,
                        testing::Values(CylinderRayHitsData{Point(1, 0, -5), Vector(0, 0, 1), 5, 5},
                                        CylinderRayHitsData{Point(0, 0, -5), Vector(0, 0, 1), 4, 6},
                                        CylinderRayHitsData{Point(0.5f, 0, -5.f),
                                                            Vector(0.1f, 1, 1), 6.8080058f,
                                                            7.0886984f}));

INSTANTIATE_TEST_CASE_P(CylinderTest, CylinderNormal,
                        testing::Values(CylinderNormalData{Point(1, 0, 0), Vector(1, 0, 0)},
                                        CylinderNormalData{Point(0, 5, -1), Vector(0, 0, -1)},
                                        CylinderNormalData{Point(0, -2, 1), Vector(0, 0, 1)},
                                        CylinderNormalData{Point(-1, 1, 0), Vector(-1, 0, 0)}));

INSTANTIATE_TEST_CASE_P(
    CylinderTest, CylinderConstrained,
    testing::Values(CylinderConstrainedOrCappedData{Point(0, 1.5f, 0), Vector(0.1f, 1, 0), 0},
                    CylinderConstrainedOrCappedData{Point(0, 3, -5), Vector(0, 0, 1), 0},
                    CylinderConstrainedOrCappedData{Point(0, 0, -5), Vector(0, 0, 1), 0},
                    CylinderConstrainedOrCappedData{Point(0, 2, -5), Vector(0, 0, 1), 0},
                    CylinderConstrainedOrCappedData{Point(0, 1, -5), Vector(0, 0, 1), 0},
                    CylinderConstrainedOrCappedData{Point(0, 1.5f, -2), Vector(0, 0, 1), 2}));

} // namespace zrt