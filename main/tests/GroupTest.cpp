#include <gtest/gtest.h>

#include "Group.h"

#include "TestUtil.h"

namespace zrt
{

TEST(GroupTest, CreateGroup)
{
    Group g{};
    EXPECT_EQ(Floats(g.Transform()), Floats(XMMatrixIdentity()));
    EXPECT_TRUE(g.Empty());
}

} // namespace zrt