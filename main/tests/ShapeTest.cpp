#include <gtest/gtest.h>

#include "Shape.h"
#include "Sphere.h"

namespace zrt
{

TEST(ShapeTest, ShapeHasParentAttribute)
{
    Sphere s{};
    EXPECT_EQ(s.Parent(), nullptr);
}

} // namespace zrt