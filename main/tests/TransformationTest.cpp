#include <gtest/gtest.h>

#include "Matrix.h"
#include "TestConstants.h"
#include "TestUtil.h"
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

TEST(TransformationTest, TransformationMatrixDefaultOrientation)
{
    auto from = Point(0, 0, 0);
    auto to = Point(0, 0, -1);
    auto up = Vector(0, 1, 0);
    auto t = ViewTransform(from, to, up);
    EXPECT_EQ(Floats(t), Floats(XMMatrixIdentity()));
}

TEST(TransformationTest, TransformationMatrixLookingPositiveZ)
{
    auto from = Point(0, 0, 0);
    auto to = Point(0, 0, 1);
    auto up = Vector(0, 1, 0);
    auto t = ViewTransform(from, to, up);
    EXPECT_EQ(Floats(t), Floats(Scaling(-1, 1, -1)));
}

TEST(TransformationTest, TransformationMatrixMovesWorld)
{
    auto from = Point(0, 0, 8);
    auto to = Point(0, 0, 0);
    auto up = Vector(0, 1, 0);
    auto t = ViewTransform(from, to, up);
    EXPECT_EQ(Floats(t), Floats(Translation(0, 0, -8)));
}

TEST(TransformationTest, TransformationMatrixArbitrary)
{
    auto from = Point(1, 3, 2);
    auto to = Point(4, -2, 8);
    auto up = Vector(0, 1, 0);
    auto t = ViewTransform(from, to, up);
    auto m =
        XMMATRIX{-0.50709f, 0.50709f, 0.67612f,  -2.36643, 0.76772f, 0.60609f, 0.12122f, -2.82843f,
                 -0.35857f, 0.59761f, -0.71714f, 0.f,      0.f,      0.f,      0.f,      1.f};
    EXPECT_EQ(Floats(t), Floats(m));
}

} // namespace zrt
