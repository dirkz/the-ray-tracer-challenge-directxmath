#include <gtest/gtest.h>

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
    ASSERT_EQ(xs[0], 4);
    ASSERT_EQ(xs[1], 6);
}

TEST(SphereTest, RayIntersectsSphereAtTangent)
{
    Ray r{Point(0, 1, -5), Vector(0, 0, 1)};
    Sphere s{};
    auto xs = s.Intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0], 5);
    ASSERT_EQ(xs[1], 5);
}

TEST(SphereTest, RayMissesSphere)
{
    Ray r{Point(0, 2, -5), Vector(0, 0, 1)};
    Sphere s{};
    auto xs = s.Intersect(r);
    ASSERT_EQ(xs.size(), 0);
}

TEST(SphereTest, RayOriginatesInsideSphere)
{
    Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
    Sphere s{};
    auto xs = s.Intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0], -1);
    ASSERT_EQ(xs[1], 0);
}

TEST(SphereTest, SphereIsBehindRay)
{
    Ray r{Point(0, 0, 5), Vector(0, 0, 1)};
    Sphere s{};
    auto xs = s.Intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0], -6);
    ASSERT_EQ(xs[1], -4);
}

} // namespace zrt
