#include <gtest/gtest.h>

#include "Sphere.h"
#include "Intersection.h"

namespace zrt
{

TEST(IntersectionTest, HitWhenAllIntersectionsHavePositiveT)
{
    Sphere s{};
    Intersection i1{s, 1};
    Intersection i2{s, 2};
    IntersectionList xs = intersections({i1, i2});
    const Intersection *pI = hit(xs);
    ASSERT_NE(pI, nullptr);
    ASSERT_EQ(*pI, i1);
}

TEST(IntersectionTest, HitWhenSomeIntersectionsHaveNegativeT)
{
    Sphere s{};
    Intersection i1{s, -1};
    Intersection i2{s, 1};
    IntersectionList xs = intersections({i1, i2});
    const Intersection *pI = hit(xs);
    ASSERT_NE(pI, nullptr);
    ASSERT_EQ(*pI, i2);
}

TEST(IntersectionTest, HitWhenAllIntersectionsHaveNegativeT)
{
    Sphere s{};
    Intersection i1{s, -2};
    Intersection i2{s, -1};
    IntersectionList xs = intersections({i1, i2});
    const Intersection *pI = hit(xs);
    ASSERT_EQ(pI, nullptr);
}

TEST(IntersectionTest, HitIsAlwaysLowestNonnegativeIntersection)
{
    Sphere s{};
    Intersection i1{s, 5};
    Intersection i2{s, 7};
    Intersection i3{s, -3};
    Intersection i4{s, 2};
    IntersectionList xs = intersections({i1, i2, i3, i4});
    const Intersection *pI = hit(xs);
    ASSERT_NE(pI, nullptr);
    ASSERT_EQ(*pI, i4);
}

} // namespace zrt
