#include "stdafx.h"

#include <gtest/gtest.h>

#include "Cube.h"
#include "Vector.h"

namespace zrt
{

struct IntersectionData
{
    IntersectionData(FXMVECTOR origin, FXMVECTOR direction, float t1, float t2) : m_t1{t1}, m_t2{t2}
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

struct IntersectionTest : public testing::TestWithParam<IntersectionData>
{
};

TEST_P(IntersectionTest, CubeIntersection)
{
}

INSTANTIATE_TEST_CASE_P(CubeTest, IntersectionTest,
                        testing::Values(IntersectionData{Point(5, 0.5f, 0), Vector(-1, 0, 0), 4, 6},
                                        IntersectionData{Point(-5, 0.5f, 0), Vector(1, 0, 0), 4, 6},
                                        IntersectionData{Point(0.5f, 5, 0), Vector(0, -1, 0), 4, 6},
                                        IntersectionData{Point(0.5, -5, 0), Vector(0, 1, 0), 4, 6},
                                        IntersectionData{Point(0.5f, 0, 5), Vector(0, 0, -1), 4, 6},
                                        IntersectionData{Point(0.5, 0, -5), Vector(0, 0, 1), 4, 6},
                                        IntersectionData{Point(0, 0.5, 0), Vector(0, 0, 1), -1,
                                                         1}));

} // namespace zrt