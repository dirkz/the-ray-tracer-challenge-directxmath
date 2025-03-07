#include <gtest/gtest.h>

#include "TestUtil.h"

#include "Triangle.h"
#include "Vector.h"

namespace zrt
{

TEST(TriangleTest, ConstructingTriangle)
{
    auto p1 = Point(0, 1, 0);
    auto p2 = Point(-1, 0, 0);
    auto p3 = Point(1, 0, 0);

    Triangle t{p1, p2, p3};

    EXPECT_EQ(Floats(p1), Floats(t.P1()));
    EXPECT_EQ(Floats(p2), Floats(t.P2()));
    EXPECT_EQ(Floats(p3), Floats(t.P3()));
    EXPECT_EQ(Floats(t.E1()), Floats(Vector(-1, -1, 0)));
    EXPECT_EQ(Floats(t.E2()), Floats(Vector(1, -1, 0)));
    EXPECT_EQ(Floats(t.Normal()), Floats(Vector(0, 0, -1)));
}

} // namespace zrt