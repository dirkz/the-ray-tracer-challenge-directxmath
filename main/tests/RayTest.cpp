#include <gtest/gtest.h>

#include "Ray.h"
#include "Vector.h"

namespace zrt
{

TEST(RayTest, CreatingAndQueryingRays)
{
    auto origin = Point(1, 2, 3);
    
    ASSERT_PRED1(IsPoint, origin);

    ASSERT_TRUE(IsPoint(origin));
    auto direction = Vector(4, 5, 6);
    ASSERT_TRUE(IsVector(direction));
    auto ray = Ray{origin, direction};
    ASSERT_TRUE(IsEqual(origin, ray.Origin()));
    ASSERT_TRUE(IsEqual(direction, ray.Direction()));
}

TEST(RayTest, ComputingPointFromDistance)
{
    auto ray = Ray{Point(2, 3, 4), Vector(1, 0, 0)};
    ASSERT_TRUE(IsEqual(ray.Position(0), Point(2, 3, 4)));
    ASSERT_TRUE(IsEqual(ray.Position(1), Point(3, 3, 4)));
    ASSERT_TRUE(IsEqual(ray.Position(-1), Point(1, 3, 4)));
    ASSERT_TRUE(IsEqual(ray.Position(2.5), Point(4.5, 3, 4)));
}

} // namespace zrt
