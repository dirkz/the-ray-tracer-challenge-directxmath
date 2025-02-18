#include <gtest/gtest.h>

#include "Matrix.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vector.h"

namespace zrt
{

TEST(SphereTest, RayIntersectsSphereTwoPoints)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    Sphere s{};
    auto xs = s.Intersect(r);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].T(), 4);
    EXPECT_EQ(xs[1].T(), 6);
}

TEST(SphereTest, RayIntersectsSphereAtTangent)
{
    Ray r{Point(0, 1, -5), Vector(0, 0, 1)};
    Sphere s{};
    auto xs = s.Intersect(r);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].T(), 5);
    EXPECT_EQ(xs[1].T(), 5);
}

TEST(SphereTest, RayMissesSphere)
{
    Ray r{Point(0, 2, -5), Vector(0, 0, 1)};
    Sphere s{};
    auto xs = s.Intersect(r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(SphereTest, RayOriginatesInsideSphere)
{
    Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
    Sphere s{};
    auto xs = s.Intersect(r);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].T(), -1);
    EXPECT_EQ(xs[1].T(), 1);
}

TEST(SphereTest, SphereIsBehindRay)
{
    Ray r{Point(0, 0, 5), Vector(0, 0, 1)};
    Sphere s{};
    auto xs = s.Intersect(r);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].T(), -6);
    EXPECT_EQ(xs[1].T(), -4);
}

TEST(SphereTest, IntersectingScaledSphereWithRay)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    Sphere s{Scaling(2, 2, 2)};
    auto xs = s.Intersect(r);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].T(), 3);
    EXPECT_EQ(xs[1].T(), 7);
}

TEST(SphereTest, IntersectingTranslatedSphereWithRay)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    Sphere s{Translation(5, 0, 0)};
    auto xs = s.Intersect(r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(SphereTest, NormalOnSphereAtPointOnXAxis)
{
    Sphere s{};
    auto p = Point(1, 0, 0);
    auto n = s.Normal(p);
    EXPECT_EQ(Floats(n), Floats(PointToVector(p)));
    EXPECT_EQ(Floats(n), Floats(XMVector4Normalize(n)));
}

TEST(SphereTest, NormalOnSphereAtPointOnYAxis)
{
    Sphere s{};
    auto p = Point(0, 1, 0);
    auto n = s.Normal(p);
    EXPECT_EQ(Floats(n), Floats(PointToVector(p)));
    EXPECT_EQ(Floats(n), Floats(XMVector4Normalize(n)));
}

TEST(SphereTest, NormalOnSphereAtPointOnZAxis)
{
    Sphere s{};
    auto p = Point(0, 0, 1);
    auto n = s.Normal(p);
    EXPECT_EQ(Floats(n), Floats(PointToVector(p)));
    EXPECT_EQ(Floats(n), Floats(XMVector4Normalize(n)));
}

TEST(SphereTest, NormalOnSphereAtNonaxialPoint)
{
    const float ThirdSqrt3 = sqrt(3.f) / 3.f;
    Sphere s{};
    auto p = Point(ThirdSqrt3);
    auto n = s.Normal(p);
    EXPECT_EQ(Floats(n), Floats(PointToVector(p)));
    EXPECT_EQ(Floats(n), Floats(XMVector4Normalize(n)));
}

} // namespace zrt
