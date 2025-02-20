#include "stdafx.h"

#include <gtest/gtest.h>

#include "PointLight.h"
#include "TestUtil.h"
#include "Vector.h"

namespace zrt
{

TEST(LightTest, PointLightHasPositionAndIntensity)
{
    auto intensity = Color(1, 1, 1);
    auto position = Point(0, 0, 0);
    auto light = PointLight{position, intensity};
    EXPECT_EQ(Floats(light.Position()), Floats(position));
    EXPECT_EQ(Floats(light.Intensity()), Floats(intensity));
}

} // namespace zrt
