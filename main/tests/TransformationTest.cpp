#include <gtest/gtest.h>

#include "Vector.h"
#include "Matrix.h"

namespace zrt
{

TEST(TransformationTest, RotatingPointAroundX)
{
    auto pi = std::numbers::pi_v<float>;
    auto halfSqrt = sqrt(2.f) / 2;
    auto p = Point(0, 1, 0);
    auto halfQuarter = RotationX(pi / 4);
    auto fullQuarter = RotationX(pi / 2);
    EXPECT_EQ(Floats(XMVector4Transform(p, halfQuarter)), Floats(Point(0, halfSqrt, halfSqrt)));
    EXPECT_EQ(Floats(XMVector4Transform(p, fullQuarter)), Floats(Point(0, 0, 1)));
}

} // namespace zrt
