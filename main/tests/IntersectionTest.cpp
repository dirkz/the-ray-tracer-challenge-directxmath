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
    IntersectionList xs = instersections({i1, i2});
    const Intersection *pI = hit(xs);
}

} // namespace zrt
