#include "stdafx.h"

#include <gtest/gtest.h>

#include "TestConstants.h"
#include "TestUtil.h"
#include "Vector.h"

namespace zrt
{

TEST(VectorTest, ReflectingVectorApproaching45)
{
    auto v = Vector(1, -1, 0);
    auto n = Vector(0, 1, 0);
    auto r = Reflect(v, n);
    EXPECT_EQ(Floats(r), Floats(Vector(1, 1, 0)));
}

TEST(VectorTest, ReflectingVectorOffSlantedSurface)
{
    auto v = Vector(0, -1, 0);
    auto n = Vector(HalfSqrt, HalfSqrt, 0);
    auto r = Reflect(v, n);
    EXPECT_EQ(Floats(r), Floats(Vector(1, 0, 0)));
}

} // namespace zrt