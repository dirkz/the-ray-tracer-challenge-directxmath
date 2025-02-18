#include <gtest/gtest.h>

#include "Constants.h"
#include "Matrix.h"
#include "Vector.h"

namespace zrt
{

TEST(TransformationTest, RotatingPointAroundX)
{
    auto p = Point(0, 1, 0);
    const XMMATRIX halfQuarter = RotationX(PI / 4);
    const XMMATRIX fullQuarter = RotationX(PI / 2);
    EXPECT_EQ(Floats(XMVector4Transform(p, halfQuarter)), Floats(Point(0, HalfSqrt, HalfSqrt)));
    EXPECT_EQ(Floats(XMVector4Transform(p, fullQuarter)), Floats(Point(0, 0, 1)));
}

TEST(TransformationTest, InverseOfXRotationRotatesInOppositeDirection)
{
    auto p = Point(0, 1, 0);
    const XMMATRIX halfQuarter = RotationX(PI / 4);
    auto inv = XMMatrixInverse(nullptr, halfQuarter);
    EXPECT_EQ(Floats(XMVector4Transform(p, inv)), Floats(Point(0, HalfSqrt, -HalfSqrt)));
}

TEST(TransformationTest, RotatingPointAroundY)
{
    auto p = Point(0, 0, 1);
    const XMMATRIX halfQuarter = RotationY(PI / 4);
    const XMMATRIX fullQuarter = RotationY(PI / 2);
    EXPECT_EQ(Floats(XMVector4Transform(p, halfQuarter)), Floats(Point(HalfSqrt, 0, HalfSqrt)));
    EXPECT_EQ(Floats(XMVector4Transform(p, fullQuarter)), Floats(Point(1, 0, 0)));
}

TEST(TransformationTest, RotatingPointAroundZ)
{
    auto p = Point(0, 1, 0);
    const XMMATRIX halfQuarter = RotationZ(PI / 4);
    const XMMATRIX fullQuarter = RotationZ(PI / 2);
    EXPECT_EQ(Floats(XMVector4Transform(p, halfQuarter)), Floats(Point(-HalfSqrt, HalfSqrt, 0)));
    EXPECT_EQ(Floats(XMVector4Transform(p, fullQuarter)), Floats(Point(-1, 0, 0)));
}

} // namespace zrt
