#include <gtest/gtest.h>

#include "Computations.h"
#include "Intersection.h"
#include "Sphere.h"
#include "TestUtil.h"

namespace zrt
{

TEST(IntersectionTest, HitWhenAllIntersectionsHavePositiveT)
{
    Sphere s{};
    Intersection i1{&s, 1};
    Intersection i2{&s, 2};
    IntersectionList xs = intersections({i1, i2});
    const Intersection *pI = hit(xs);
    ASSERT_NE(pI, nullptr);
    ASSERT_EQ(*pI, i1);
}

TEST(IntersectionTest, HitWhenSomeIntersectionsHaveNegativeT)
{
    Sphere s{};
    Intersection i1{&s, -1};
    Intersection i2{&s, 1};
    IntersectionList xs = intersections({i1, i2});
    const Intersection *pI = hit(xs);
    ASSERT_NE(pI, nullptr);
    ASSERT_EQ(*pI, i2);
}

TEST(IntersectionTest, HitWhenAllIntersectionsHaveNegativeT)
{
    Sphere s{};
    Intersection i1{&s, -2};
    Intersection i2{&s, -1};
    IntersectionList xs = intersections({i1, i2});
    const Intersection *pI = hit(xs);
    ASSERT_EQ(pI, nullptr);
}

TEST(IntersectionTest, HitIsAlwaysLowestNonnegativeIntersection)
{
    Sphere s{};
    Intersection i1{&s, 5};
    Intersection i2{&s, 7};
    Intersection i3{&s, -3};
    Intersection i4{&s, 2};
    IntersectionList xs = intersections({i1, i2, i3, i4});
    const Intersection *pI = hit(xs);
    EXPECT_NE(pI, nullptr);
    EXPECT_EQ(*pI, i4);
}

TEST(IntersectionTest, PrecomputingStateOfIntersection)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    Sphere shape{};
    Intersection i{&shape, 4};
    Computations comps{i, r};
    EXPECT_EQ(comps.Object(), i.Object());
    EXPECT_EQ(Floats(comps.Point()), Floats(Point(0, 0, -1)));
    EXPECT_EQ(Floats(comps.EyeV()), Floats(Vector(0, 0, -1)));
    EXPECT_EQ(Floats(comps.Normal()), Floats(Vector(0, 0, -1)));
}

} // namespace zrt
