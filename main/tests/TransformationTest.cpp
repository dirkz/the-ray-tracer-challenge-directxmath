#include <gtest/gtest.h>

#include "Matrix.h"
#include "Vector.h"

namespace zrt
{

constexpr float pi = std::numbers::pi_v<float>;
const float halfSqrt = sqrt(2.f) / 2;

TEST(TransformationTest, RotatingPointAroundX)
{
    auto p = Point(0, 1, 0);
    const XMMATRIX halfQuarter = RotationX(pi / 4);
    const XMMATRIX fullQuarter = RotationX(pi / 2);
    EXPECT_EQ(Floats(XMVector4Transform(p, halfQuarter)), Floats(Point(0, halfSqrt, halfSqrt)));
    EXPECT_EQ(Floats(XMVector4Transform(p, fullQuarter)), Floats(Point(0, 0, 1)));
}

TEST(TransformationTest, InverseOfXRotationRotatesInOppositeDirection)
{
    auto p = Point(0, 1, 0);
    const XMMATRIX halfQuarter = RotationX(pi / 4);
    auto inv = XMMatrixInverse(nullptr, halfQuarter);
    EXPECT_EQ(Floats(XMVector4Transform(p, inv)), Floats(Point(0, halfSqrt, -halfSqrt)));
}

TEST(TransformationTest, RotatingPointAroundY)
{
    auto p = Point(0, 0, 1);
    const XMMATRIX halfQuarter = RotationY(pi / 4);
    const XMMATRIX fullQuarter = RotationY(pi / 2);
    EXPECT_EQ(Floats(XMVector4Transform(p, halfQuarter)), Floats(Point(halfSqrt, 0, halfSqrt)));
    EXPECT_EQ(Floats(XMVector4Transform(p, fullQuarter)), Floats(Point(1, 0, 0)));
}

} // namespace zrt
