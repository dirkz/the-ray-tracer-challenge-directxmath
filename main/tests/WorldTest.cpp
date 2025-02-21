#include "stdafx.h"

#include <gtest/gtest.h>

#include "Material.h"
#include "Matrix.h"
#include "PointLight.h"
#include "Sphere.h"
#include "TestConstants.h"
#include "TestUtil.h"
#include "Vector.h"
#include "World.h"

namespace zrt
{

constexpr float WorldMaterial1DefaultAmbient = 0.1f;
constexpr float WorldMaterial1DefaultDiffuse = 0.7f;
constexpr float WorldMaterial1DefaultSpecular = 0.2f;

static const Material M1 = Material{Color(0.8f, 1, 0.6f), WorldMaterial1DefaultAmbient,
                                    WorldMaterial1DefaultDiffuse, WorldMaterial1DefaultSpecular};
static const PointLight PL{Point(-10, 10, -10), Color(1, 1, 1)};

static World DefaultWorld(const PointLight &light = PL, const Material &m1 = M1,
                          const Material &m2 = Material{})
{
    Intersectable *s1 = new Sphere{XMMatrixIdentity(), m1};
    Intersectable *s2 = new Sphere{Scaling(0.5f, 0.5f, 0.5f), m2};

    World w{light, {s1, s2}};

    EXPECT_EQ(w.Lights().size(), 1);
    PointLight light2 = w.Lights()[0];
    EXPECT_EQ(light2, light);

    auto itS1 = std::find(w.Objects().begin(), w.Objects().end(), s1);
    auto itS2 = std::find(w.Objects().begin(), w.Objects().end(), s2);

    EXPECT_TRUE(itS1 != w.Objects().end());

    return w;
}

TEST(WorldTest, CreatingWorld)
{
    World w{};
    EXPECT_TRUE(w.Lights().empty());
    EXPECT_TRUE(w.Objects().empty());
}

TEST(WorldTest, DefaultWorld)
{
    auto w = DefaultWorld();

    EXPECT_FLOAT_EQ(w.Objects()[0]->Material().Ambient(), WorldMaterial1DefaultAmbient);
    EXPECT_FLOAT_EQ(w.Objects()[0]->Material().Diffuse(), WorldMaterial1DefaultDiffuse);
    EXPECT_FLOAT_EQ(w.Objects()[0]->Material().Specular(), WorldMaterial1DefaultSpecular);
}

TEST(WorldTest, IntersectWorldRay)
{
    auto w = DefaultWorld();
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    auto xs = w.Intersect(r);
    ASSERT_EQ(xs.size(), 4);
    EXPECT_EQ(xs[0].T(), 4);
    EXPECT_EQ(xs[1].T(), 4.5f);
    EXPECT_EQ(xs[2].T(), 5.5f);
    EXPECT_EQ(xs[3].T(), 6);
}

TEST(WorldTest, ShadingIntersection)
{
    auto w = DefaultWorld();
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    auto shape = w.Objects()[0];
    Intersection i{shape, 4};
    Computations comps{i, r};
    auto c = w.ShadeHit(comps);
    EXPECT_EQ(Floats(c), Floats(Color(0.38066f, 0.47583f, 0.2855f)));
}

TEST(WorldTest, ShadingIntersectionFromOutside)
{
    auto w = DefaultWorld(PointLight{Point(0, 0.25f, 0), Color(1, 1, 1)});
    Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
    auto shape = w.Objects()[1];
    Intersection i{shape, 0.5};
    Computations comps{i, r};
    auto c = w.ShadeHit(comps);
    EXPECT_EQ(Floats(c), Floats(Color(0.90498f, 0.90498f, 0.90498f)));
}

TEST(WorldTest, ColorWhenRayMisses)
{
    auto w = DefaultWorld();
    Ray r{Point(0, 0, -5), Vector(0, 1, 0)};
    auto c = w.ColorAt(r);
    EXPECT_EQ(Floats(c), Floats(Color(0, 0, 0)));
}

TEST(WorldTest, ColorWhenRayHits)
{
    auto w = DefaultWorld();
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    auto c = w.ColorAt(r);
    EXPECT_EQ(Floats(c), Floats(Color(0.38066f, 0.47583f, 0.2855f)));
}

TEST(WorldTest, ColorWithIntersectionBehindRay)
{
    Material m1 = M1;
    m1.Ambient(1);
    Material m2{};
    m2.Ambient(1);
    auto w = DefaultWorld(PL, m1, m2);
    Ray r{Point(0, 0, 0.75f), Vector(0, 0, -1)};
    auto c = w.ColorAt(r);
    EXPECT_EQ(Floats(c), Floats(m2.Color()));
}

} // namespace zrt
