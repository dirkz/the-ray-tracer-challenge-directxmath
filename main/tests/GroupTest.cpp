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
}

} // namespace zrt