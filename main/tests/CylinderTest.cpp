#include <gtest/gtest.h>

#include "Cube.h"
#include "TestUtil.h"
#include "Vector.h"

namespace zrt
{

struct RayMissData
{
    RayMissData(FXMVECTOR origin, FXMVECTOR direction)
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

struct RayMiss : public testing::TestWithParam<RayMissData>
{
};

TEST_P(RayMiss, RayMisses)
{
}

INSTANTIATE_TEST_CASE_P(CylinderTest, RayMiss,
    testing::Values(RayMissData{Point(), Point()}));

} // namespace zrt