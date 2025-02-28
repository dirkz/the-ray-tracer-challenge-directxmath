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

struct CylinderRayMiss : public testing::TestWithParam<CylinderRayMissData>
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

INSTANTIATE_TEST_CASE_P(CylinderTest, CylinderRayMiss,
                        testing::Values(CylinderRayMissData{Point(1, 0, 0), Vector(0, 1, 0)},
                                        CylinderRayMissData{Point(0, 0, 0), Vector(0, 1, 0)},
                                        CylinderRayMissData{Point(0, 0, -5), Vector(1, 1, 1)}));

} // namespace zrt