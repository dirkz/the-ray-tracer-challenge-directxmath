#include "stdafx.h"

#include <gtest/gtest.h>

#include "Material.h"
#include "Matrix.h"
#include "Plane.h"
#include "PointLight.h"
#include "Sphere.h"
#include "TestConstants.h"
#include "TestUtil.h"
#include "Vector.h"
#include "World.h"

namespace zrt
{

TEST(WorldTest, CreatingWorld)
{
    World w{};
    EXPECT_TRUE(w.Lights().empty());
    EXPECT_TRUE(w.Shapes().empty());
}

TEST(WorldTest, DefaultWorld)
{
    auto w = DefaultWorld();

    EXPECT_FLOAT_EQ(w.Shapes()[0]->Material().Ambient(), WorldMaterial1DefaultAmbient);
    EXPECT_FLOAT_EQ(w.Shapes()[0]->Material().Diffuse(), WorldMaterial1DefaultDiffuse);
    EXPECT_FLOAT_EQ(w.Shapes()[0]->Material().Specular(), WorldMaterial1DefaultSpecular);
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
    auto shape = w.Shapes()[0];
    Intersection i{shape, 4};
    Computations comps{i, r};
    auto c = w.ShadeHit(comps);
    EXPECT_EQ(Floats(c), Floats(Color(0.38066f, 0.47583f, 0.2855f)));
}

TEST(WorldTest, ShadingIntersectionFromOutside)
{
    auto w = DefaultWorld(PointLight{Point(0, 0.25f, 0), Color(1, 1, 1)});
    Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
    auto shape = w.Shapes()[1];
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
    Material m1 = DefaultWorldMaterial1;
    m1.Ambient(1);
    Material m2{};
    m2.Ambient(1);
    auto w = DefaultWorld(DefaultWorldLight, m1, m2);
    Ray r{Point(0, 0, 0.75f), Vector(0, 0, -1)};
    auto c = w.ColorAt(r);
    EXPECT_EQ(Floats(c), Floats(m2.Color()));
}

TEST(WorldTest, ReflectedColorForNonReflectiveMaterial)
{
    Material m2{Color(1, 1, 1), 1};
    auto w = DefaultWorld(DefaultWorldLight, DefaultWorldMaterial1, m2);
    Ray r{Point(), Vector(0, 0, 1)};
    auto shape = w.Shapes()[1];
    Intersection i{shape, 1};
    Computations comps{i, r};
    auto color = w.ReflectedColor(comps);
    EXPECT_EQ(Floats(color), Floats(Color()));
}

TEST(WorldTest, ReflectedColorForReflectiveMaterial)
{
    auto w = DefaultWorld();
    Material m{MaterialDefaultColor,    MaterialDefaultAmbient,   MaterialDefaultDiffuse,
               MaterialDefaultSpecular, MaterialDefaultShininess, 0.5f};
    auto shape = new Plane{Translation(0, -1, 0), m};
    w.Add(shape);
}

} // namespace zrt
