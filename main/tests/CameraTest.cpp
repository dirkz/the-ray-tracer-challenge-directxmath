#include "stdafx.h"

#include <gtest/gtest.h>

#include "Camera.h"
#include "TestConstants.h"
#include "TestUtil.h"

namespace zrt
{

TEST(CameraTest, ConstructingCamera)
{
    constexpr unsigned hsize = 160;
    constexpr unsigned vsize = 120;
    const float fov = HalfPI;
    Camera c{hsize, vsize, fov};
    EXPECT_EQ(c.HSize(), hsize);
    EXPECT_EQ(c.VSize(), vsize);
    EXPECT_EQ(c.Fov(), fov);
    EXPECT_EQ(Floats(c.Transform()), Floats(XMMatrixIdentity()));
}

} // namespace zrt