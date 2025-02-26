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

struct IndexN1N2
{
    unsigned index;
    float n1;
    float n2;
};

struct IndexN1N2Test : public testing::TestWithParam<IndexN1N2>
{
};

TEST_P(IndexN1N2Test, FindingN1AndN2AtVariousIntersections)
{
    IndexN1N2 param = GetParam();
}

INSTANTIATE_TEST_CASE_P(HardCoded, IndexN1N2Test,
                        testing::Values(IndexN1N2{0, 1.f, 1.5f}, IndexN1N2{1, 1.5f, 2.f},
                                        IndexN1N2{2, 2.f, 2.5f}, IndexN1N2{3, 2.5f, 2.5f},
                                        IndexN1N2{4, 2.5f, 1.5f}, IndexN1N2{5, 1.5f, 1.0f}));

} // namespace zrt
