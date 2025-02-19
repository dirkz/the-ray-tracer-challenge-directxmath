#include <gtest/gtest.h>

#include "TestConstants.h"
#include "TestUtil.h"
#include "World.h"

namespace zrt
{

TEST(WorldTest, CreatingWorld)
{
    World w{};
    EXPECT_EQ(w.Light(), nullptr);
    EXPECT_TRUE(w.Objects().empty());
}

} // namespace zrt
