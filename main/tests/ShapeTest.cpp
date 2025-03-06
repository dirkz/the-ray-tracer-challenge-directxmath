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

TEST(ShapeTest, ConvertingNormalFromObjectToWorldSpace)
{
    Group g1{RotationY(HalfPI)};
    Group g2{Scaling(1, 2, 3)};
    g1.Add(&g2);
    Sphere s{Translation(5, 0, 0)};
    g2.Add(&s);
    auto n = s.ObjectToWorldNormal(Vector(ThirdSqrt, ThirdSqrt, ThirdSqrt));
    EXPECT_EQ(Floats(n), Floats(Vector(0.2857f, 0.4286f, -0.8571f)));
}

TEST(ShapeTest, FindingTheNormalOnChildObject)
{
    Group g1{RotationY(HalfPI)};
    Group g2{Scaling(1, 2, 3)};
    g1.Add(&g2);
    Sphere s{Translation(5, 0, 0)};
    g2.Add(&s);
    auto n = s.Normal(Point(1.7321f, 1.1547f, -5.5774f));
    EXPECT_EQ(Floats(n), Floats(Vector(0.2857f, 0.4286f, -0.8571f)));
}

} // namespace zrt