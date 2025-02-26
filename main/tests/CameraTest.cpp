#include "stdafx.h"

#include <gtest/gtest.h>

#include "Camera.h"
#include "Matrix.h"
#include "Render.h"
#include "TestConstants.h"
#include "TestUtil.h"
#include "Vector.h"

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

TEST(CameraTest, PixelSizeForHorizontalCanvas)
{
    Camera c{200, 125, HalfPI};
    EXPECT_FLOAT_EQ(c.PixelSize(), 0.01f);
}

TEST(CameraTest, PixelSizeForVerticalCanvas)
{
    Camera c{125, 200, HalfPI};
    EXPECT_FLOAT_EQ(c.PixelSize(), 0.01f);
}

TEST(CameraTest, ConstructingRayThroughCenterOfCanvas)
{
    Camera c{201, 101, HalfPI};
    Ray r = c.RayForPixel(100, 50);
    EXPECT_EQ(Floats(r.Origin()), Floats(Point(0, 0, 0)));
    EXPECT_EQ(Floats(r.Direction()), Floats(Vector(0, 0, -1)));
}

TEST(CameraTest, ConstructingRayThroughCornerOfCanvas)
{
    Camera c{201, 101, HalfPI};
    Ray r = c.RayForPixel(0, 0);
    EXPECT_EQ(Floats(r.Origin()), Floats(Point(0, 0, 0)));
    EXPECT_EQ(Floats(r.Direction()), Floats(Vector(0.66519f, 0.33259f, -0.66851f)));
}

TEST(CameraTest, ConstructingRayWhenCameraIsTransformed)
{
    auto transform = XMMatrixMultiply(Translation(0, -2, 5), RotationY(QuarterPI));
    Camera c{201, 101, HalfPI, transform};
    Ray r = c.RayForPixel(100, 50);
    EXPECT_EQ(Floats(r.Origin()), Floats(Point(0, 2, -5)));
    EXPECT_EQ(Floats(r.Direction()), Floats(Vector(HalfSqrt, 0, -HalfSqrt)));
}

} // namespace zrt