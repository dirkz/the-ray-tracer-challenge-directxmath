#include <gtest/gtest.h>

#include "TestUtil.h"

#include "Triangle.h"
#include "Vector.h"

namespace zrt
{

TEST(TriangleTest, ConstructingTriangle)
{
    auto p1 = Point(0, 1, 0);
    auto p2 = Point(-1, 0, 0);
    auto p3 = Point(1, 0, 0);

    Triangle t{p1, p2, p3};

    EXPECT_EQ(Floats(p1), Floats(t.P1()));
    EXPECT_EQ(Floats(p2), Floats(t.P2()));
    EXPECT_EQ(Floats(p3), Floats(t.P3()));
    EXPECT_EQ(Floats(t.E1()), Floats(Vector(-1, -1, 0)));
    EXPECT_EQ(Floats(t.E2()), Floats(Vector(1, -1, 0)));
    EXPECT_EQ(Floats(t.Normal()), Floats(Vector(0, 0, -1)));
}

TEST(TriangleTest, FindingNormal)
{
    Triangle t{Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0)};

    auto n1 = t.LocalNormal(Point(0, 0.5f, 0));
    auto n2 = t.LocalNormal(Point(-0.5f, 0.75f, 0));
    auto n3 = t.LocalNormal(Point(0.5f, 0.25f, 0));

    EXPECT_EQ(Floats(n1), Floats(t.Normal()));
    EXPECT_EQ(Floats(n2), Floats(t.Normal()));
    EXPECT_EQ(Floats(n3), Floats(t.Normal()));
}

TEST(TriangleTest, IntersectingRayParallelToTriangle)
{
    Triangle t{Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0)};
    Ray r{Point(0, -1, -2), Vector(0, 1, 0)};
    auto xs = t.LocalIntersect(r);
    EXPECT_TRUE(xs.empty());
}

TEST(TriangleTest, RayMissesP1P3Edge)
{
    Triangle t{Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0)};
    Ray r{Point(1, 1, -2), Vector(0, 0, 1)};
    auto xs = t.LocalIntersect(r);
    EXPECT_TRUE(xs.empty());
}

TEST(TriangleTest, RayMissesP1P2Edge)
{
    Triangle t{Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0)};
    Ray r{Point(-1, 1, -2), Vector(0, 0, 1)};
    auto xs = t.LocalIntersect(r);
    EXPECT_TRUE(xs.empty());
}

TEST(TriangleTest, RayMissesP2P3Edge)
{
    Triangle t{Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0)};
    Ray r{Point(0, -1, -2), Vector(0, 0, 1)};
    auto xs = t.LocalIntersect(r);
    EXPECT_TRUE(xs.empty());
}

} // namespace zrt