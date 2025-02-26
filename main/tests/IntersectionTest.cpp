#include "stdafx.h"

#include <gtest/gtest.h>

#include "Computations.h"
#include "Intersection.h"
#include "Plane.h"
#include "Sphere.h"
#include "TestConstants.h"
#include "TestUtil.h"

namespace zrt
{

TEST(IntersectionTest, HitWhenAllIntersectionsHavePositiveT)
{
    Sphere s{};
    Intersection i1{&s, 1};
    Intersection i2{&s, 2};
    auto xs = Intersections({i1, i2});
    const Intersection *pI = Hit(xs);
    ASSERT_NE(pI, nullptr);
    ASSERT_EQ(*pI, i1);
}

TEST(IntersectionTest, HitWhenSomeIntersectionsHaveNegativeT)
{
    Sphere s{};
    Intersection i1{&s, -1};
    Intersection i2{&s, 1};
    auto xs = Intersections({i1, i2});
    const Intersection *pI = Hit(xs);
    ASSERT_NE(pI, nullptr);
    ASSERT_EQ(*pI, i2);
}

TEST(IntersectionTest, HitWhenAllIntersectionsHaveNegativeT)
{
    Sphere s{};
    Intersection i1{&s, -2};
    Intersection i2{&s, -1};
    auto xs = Intersections({i1, i2});
    const Intersection *pI = Hit(xs);
    ASSERT_EQ(pI, nullptr);
}

TEST(IntersectionTest, HitIsAlwaysLowestNonnegativeIntersection)
{
    Sphere s{};
    Intersection i1{&s, 5};
    Intersection i2{&s, 7};
    Intersection i3{&s, -3};
    Intersection i4{&s, 2};
    auto xs = Intersections({i1, i2, i3, i4});
    const Intersection *pI = Hit(xs);
    EXPECT_NE(pI, nullptr);
    EXPECT_EQ(*pI, i4);
}

TEST(IntersectionTest, PrecomputingStateOfIntersection)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    Sphere shape{};
    Intersection i{&shape, 4};
    Computations comps{i, r, {i}};
    EXPECT_EQ(comps.Object(), i.Object());
    EXPECT_EQ(Floats(comps.Point()), Floats(Point(0, 0, -1)));
    EXPECT_EQ(Floats(comps.EyeV()), Floats(Vector(0, 0, -1)));
    EXPECT_EQ(Floats(comps.Normal()), Floats(Vector(0, 0, -1)));
}

TEST(IntersectionTest, HitWhenIntersectionOccursOutside)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    Sphere shape{};
    Intersection i{&shape, 4};
    Computations comps{i, r, {i}};
    EXPECT_FALSE(comps.IsInside());
}

TEST(IntersectionTest, HitWhenIntersectionOccursInside)
{
    Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
    Sphere shape{};
    Intersection i{&shape, 1};
    Computations comps{i, r, {i}};
    EXPECT_TRUE(comps.IsInside());
    EXPECT_EQ(Floats(comps.Point()), Floats(Point(0, 0, 1)));
    EXPECT_EQ(Floats(comps.EyeV()), Floats(Vector(0, 0, -1)));
    EXPECT_EQ(Floats(comps.Normal()), Floats(Vector(0, 0, -1)));
}

TEST(IntersectionTest, PrecomputingReflectionVector)
{
    Plane shape{};
    Ray r{Point(0, 1, -1), Vector(0, -HalfSqrt, HalfSqrt)};
    Intersection i{&shape, HalfSqrt};
    Computations comps{i, r, {i}};
    EXPECT_EQ(Floats(comps.ReflectV()), Floats(Vector(0, HalfSqrt, HalfSqrt)));
}

} // namespace zrt
