#include <gtest/gtest.h>

#include "Cube.h"
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
}

INSTANTIATE_TEST_CASE_P(CylinderTest, CylinderRayMiss,
                        testing::Values(CylinderRayMissData{Point(1, 0, 0), Vector(0, 1, 0)}));

} // namespace zrt