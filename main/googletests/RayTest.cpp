#include "stdafx.h"

#include <gtest/gtest.h>

#include "Matrix.h"
#include "Ray.h"
#include "TestUtil.h"
#include "Vector.h"

namespace zrt
{

TEST(RayTest, CreatingAndQueryingRays)
{
    auto origin = Point(1, 2, 3);
    ASSERT_TRUE(IsPoint(origin)) << Floats(origin) << " must be a point";
    auto direction = Vector(4, 5, 6);
    ASSERT_TRUE(IsVector(direction)) << Floats(direction) << " must be a vector";
    auto ray = Ray{origin, direction};
    EXPECT_EQ(Floats(origin), Floats(ray.Origin()));
    EXPECT_EQ(Floats(direction), Floats(ray.Direction()));
}

TEST(RayTest, ComputingPointFromDistance)
{
    auto ray = Ray{Point(2, 3, 4), Vector(1, 0, 0)};
    EXPECT_EQ(Floats(ray.Position(0)), Floats(Point(2, 3, 4)));
    EXPECT_EQ(Floats(ray.Position(0)), Floats(Point(2, 3, 4)));
    EXPECT_EQ(Floats(ray.Position(1)), Floats(Point(3, 3, 4)));
    EXPECT_EQ(Floats(ray.Position(-1)), Floats(Point(1, 3, 4)));
    EXPECT_EQ(Floats(ray.Position(2.5)), Floats(Point(4.5, 3, 4)));
}

TEST(RayTest, TranslatingRay)
{
    auto r = Ray{Point(1, 2, 3), Vector(0, 1, 0)};
    auto m = Translation(3, 4, 5);
    auto r2 = r.Transform(m);
    EXPECT_EQ(Floats(r2.Origin()), Floats(Point(4, 6, 8)));
    EXPECT_EQ(Floats(r2.Direction()), Floats(Vector(0, 1, 0)));
}

TEST(RayTest, ScalingRay)
{
    auto r = Ray{Point(1, 2, 3), Vector(0, 1, 0)};
    auto m = Scaling(2, 3, 4);
    auto r2 = r.Transform(m);
    EXPECT_EQ(Floats(r2.Origin()), Floats(Point(2, 6, 12)));
    EXPECT_EQ(Floats(r2.Direction()), Floats(Vector(0, 3, 0)));
}

} // namespace zrt
