#include <gtest/gtest.h>

#include "Material.h"
#include "TestConstants.h"
#include "TestUtil.h"
#include "Vector.h"

namespace zrt
{

TEST(MaterialTest, DefaultMaterial)
{
    Material m{};
    EXPECT_EQ(Floats(m.Color()), Floats(Color(1, 1, 1)));
    EXPECT_FLOAT_EQ(m.Ambient(), 0.1f);
    EXPECT_FLOAT_EQ(m.Diffuse(), 0.9f);
    EXPECT_FLOAT_EQ(m.Specular(), 0.9f);
    EXPECT_FLOAT_EQ(m.Shininess(), 200.f);
}

TEST(MaterialTest, LightingWithEyeBetweenLightAndSurface)
{
    Material m{};
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight{Point(0, 0, -10), Color(1, 1, 1)};
    auto result = m.Lighting(light, position, eyev, normalv);
    EXPECT_EQ(Floats(result), Floats(Color(1.9f, 1.9f, 1.9f)));
}

TEST(MaterialTest, LightingWithEyeBetweenLightAndSurfaceEyeOffset45)
{
    Material m{};
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, HalfSqrt, -HalfSqrt);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight{Point(0, 0, -10), Color(1, 1, 1)};
    auto result = m.Lighting(light, position, eyev, normalv);
    EXPECT_EQ(Floats(result), Floats(Color(1.0f, 1.0f, 1.0f)));
}

TEST(MaterialTest, LightingWithEyeOppositeSurfaceEyeOffset45)
{
    Material m{};
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight{Point(0, 10, -10), Color(1, 1, 1)};
    auto result = m.Lighting(light, position, eyev, normalv);
    EXPECT_EQ(Floats(result), Floats(Color(0.7364f, 0.7364f, 0.7364f)));
}

TEST(MaterialTest, LightingWithEyeInPathOfReflectionVector)
{
    Material m{};
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, -HalfSqrt, -HalfSqrt);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight{Point(0, 10, -10), Color(1, 1, 1)};
    auto result = m.Lighting(light, position, eyev, normalv);
    EXPECT_EQ(Floats(result), Floats(Color(1.6364f, 1.6364f, 1.6364f)));
}

TEST(MaterialTest, LightingWithLightBehindSurface)
{
    Material m{};
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight{Point(0, 0, 10), Color(1, 1, 1)};
    auto result = m.Lighting(light, position, eyev, normalv);
    EXPECT_EQ(Floats(result), Floats(Color(0.1f, 0.1f, 0.1f)));
}

} // namespace zrt
