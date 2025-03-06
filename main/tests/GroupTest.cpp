#include <gtest/gtest.h>

#include "TestUtil.h"

#include "Group.h"
#include "Ray.h"

namespace zrt
{

TEST(GroupTest, CreateGroup)
{
    Group g{};
    EXPECT_EQ(Floats(g.Transform()), Floats(XMMatrixIdentity()));
    EXPECT_TRUE(g.Empty());
}

TEST(GroupTest, AddChildToGroup)
{
    Group g{};
    Sphere s{};
    g.Add(&s);
    EXPECT_FALSE(g.Empty());
    EXPECT_EQ(s.Parent(), &g);
    EXPECT_TRUE(g.Contains(&s));
}

TEST(GroupTest, IntersectingRayWithEmptyGroup)
{
    Group g{};
    Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
    auto xs = g.LocalIntersect(r);
    EXPECT_TRUE(xs.empty());
}

TEST(GroupTest, IntersectingRayWithNonemptyGroup)
{
    Group g{};
    Sphere s1{};
    Sphere s2{Translation(0, 0, -3)};
    Sphere s3{Translation(5, 0, 0)};
    g.Add(&s1);
    g.Add(&s2);
    g.Add(&s3);
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    auto xs = g.LocalIntersect(r);
    ASSERT_EQ(xs.size(), 4);
    EXPECT_EQ(xs[0].Object(), &s2);
    EXPECT_EQ(xs[1].Object(), &s2);
    EXPECT_EQ(xs[2].Object(), &s1);
    EXPECT_EQ(xs[3].Object(), &s1);
}

} // namespace zrt