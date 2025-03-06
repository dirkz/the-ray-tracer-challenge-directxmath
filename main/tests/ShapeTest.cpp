#include <gtest/gtest.h>

#include "TestConstants.h"
#include "TestUtil.h"

#include "Group.h"
#include "Matrix.h"
#include "Shape.h"
#include "Sphere.h"

namespace zrt
{

TEST(ShapeTest, ShapeHasParentAttribute)
{
    Sphere s{};
    EXPECT_EQ(s.Parent(), nullptr);
}

TEST(ShapeTest, ConvertingPointFromWorldToObjectSpace)
{
    Group g1{RotationY(HalfPI)};
    Group g2{Scaling(2, 2, 2)};
    g1.Add(&g2);
    Sphere s{Translation(5, 0, 0)};
    g2.Add(&s);
    auto p = s.WorldToObjectPoint(Point(-2, 0, -10));
    EXPECT_EQ(Floats(p), Floats(Point(0, 0, -1)));
}

} // namespace zrt