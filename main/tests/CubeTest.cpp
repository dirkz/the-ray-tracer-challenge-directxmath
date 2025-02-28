#include "stdafx.h"

#include <gtest/gtest.h>

#include "Cube.h"
#include "Vector.h"

namespace zrt
{

struct IntersectionDataHit
{
    IntersectionDataHit(FXMVECTOR origin, FXMVECTOR direction, float t1, float t2)
        : m_t1{t1}, m_t2{t2}
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

struct IntersectionDataMiss
{
    IntersectionDataMiss(FXMVECTOR origin, FXMVECTOR direction)
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

struct IntersectionTestHit : public testing::TestWithParam<IntersectionDataHit>
{
};

struct IntersectionTestMiss : public testing::TestWithParam<IntersectionDataMiss>
{
};

TEST_P(IntersectionTestHit, CubeIntersection)
{
    IntersectionDataHit param = GetParam();

    Cube c{};
    Ray r{param.Origin(), param.Direction()};

    auto xs = c.Intersect(r);

    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].T(), param.T1());
    EXPECT_FLOAT_EQ(xs[1].T(), param.T2());
}

TEST_P(IntersectionTestMiss, RayMisses)
{
    IntersectionDataMiss param = GetParam();

    Cube c{};
    Ray r{param.Origin(), param.Direction()};

    auto xs = c.Intersect(r);

    EXPECT_EQ(xs.size(), 0);
}

INSTANTIATE_TEST_CASE_P(
    CubeTest, IntersectionTestHit,
    testing::Values(IntersectionDataHit{Point(5, 0.5f, 0), Vector(-1, 0, 0), 4, 6},
                    IntersectionDataHit{Point(-5, 0.5f, 0), Vector(1, 0, 0), 4, 6},
                    IntersectionDataHit{Point(0.5f, 5, 0), Vector(0, -1, 0), 4, 6},
                    IntersectionDataHit{Point(0.5, -5, 0), Vector(0, 1, 0), 4, 6},
                    IntersectionDataHit{Point(0.5f, 0, 5), Vector(0, 0, -1), 4, 6},
                    IntersectionDataHit{Point(0.5, 0, -5), Vector(0, 0, 1), 4, 6},
                    IntersectionDataHit{Point(0, 0.5, 0), Vector(0, 0, 1), -1, 1}));

INSTANTIATE_TEST_CASE_P(
    CubeTest, IntersectionTestMiss,
    testing::Values(IntersectionDataMiss{Point(-2, 0, 0), Vector(0.2673f, 0.5345f, 0.8018f)},
                    IntersectionDataMiss{Point(0, -2, 0), Vector(0.8018f, 0.2673f, 0.5345f)},
                    IntersectionDataMiss{Point(0, 0, -2), Vector(0.5345f, 0.8018f, 0.2673f)},
                    IntersectionDataMiss{Point(2, 0, 2), Vector(0, 0, -1)},
                    IntersectionDataMiss{Point(0, 2, 2), Vector(0, -1, 0)},
                    IntersectionDataMiss{Point(2, 2, 0), Vector(-1, 0, 0)}));

} // namespace zrt