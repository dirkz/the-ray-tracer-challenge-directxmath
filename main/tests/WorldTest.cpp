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
    Computations comps{i, r, {i}};
    auto c = w.ShadeHit(comps, 1);
    EXPECT_EQ(Floats(c), Floats(Color(0.38066f, 0.47583f, 0.2855f)));
}

TEST(WorldTest, ShadingIntersectionFromOutside)
{
    auto w = DefaultWorld(PointLight{Point(0, 0.25f, 0), Color(1, 1, 1)});
    Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
    auto shape = w.Shapes()[1];
    Intersection i{shape, 0.5};
    Computations comps{i, r, {i}};
    auto c = w.ShadeHit(comps, 1);
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
    Computations comps{i, r, {i}};
    auto color = w.ReflectedColor(comps, 1);
    EXPECT_EQ(Floats(color), Floats(Color()));
}

TEST(WorldTest, ReflectedColorForReflectiveMaterial)
{
    auto w = DefaultWorld();

    Material m{MaterialDefaultColor,    MaterialDefaultAmbient,   MaterialDefaultDiffuse,
               MaterialDefaultSpecular, MaterialDefaultShininess, 0.5f};
    auto shape = new Plane{Translation(0, -1, 0), m};

    w.Add(shape);

    Ray r{Point(0, 0, -3), Vector(0, -HalfSqrt, HalfSqrt)};

    Intersection i{shape, sqrt(2.f)};
    Computations comps{i, r, {i}};
    auto color = w.ReflectedColor(comps, 1);

    EXPECT_EQ(Floats(color), Floats(Color(0.19032f, 0.2379f, 0.14274f)));
}

TEST(WorldTest, ShadeHitForReflectiveMaterial)
{
    auto w = DefaultWorld();

    Material m{MaterialDefaultColor,    MaterialDefaultAmbient,   MaterialDefaultDiffuse,
               MaterialDefaultSpecular, MaterialDefaultShininess, 0.5f};
    auto shape = new Plane{Translation(0, -1, 0), m};

    w.Add(shape);

    Ray r{Point(0, 0, -3), Vector(0, -HalfSqrt, HalfSqrt)};

    Intersection i{shape, sqrt(2.f)};
    Computations comps{i, r, {i}};
    auto color = w.ShadeHit(comps, 1);

    EXPECT_EQ(Floats(color), Floats(Color(0.87677f, 0.92436f, 0.82918f)));
}

TEST(WorldTest, ColorAtWithMutuallyReflectiveSurfaces)
{
    PointLight light{Point(), Color(1, 1, 1)};

    Material reflectiveM{MaterialDefaultColor,    MaterialDefaultAmbient,   MaterialDefaultDiffuse,
                         MaterialDefaultSpecular, MaterialDefaultShininess, 1.f};

    auto t1 = Translation(0, -1, 0);
    auto t2 = Translation(0, 1, 0);

    Plane *p1 = new Plane{t1, reflectiveM};
    Plane *p2 = new Plane{t2, reflectiveM};

    World w{light, {p1, p2}};

    Ray r{Point(), Vector(0, 1, 0)};
    auto c = w.ColorAt(r);
}

TEST(WorldTest, RefractedColorWithOpaqueSurface)
{
    World w = DefaultWorld();
    const Shape *shape = w.Shapes()[0];
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    auto xs = Intersections({{shape, 4}, {shape, 6}});
    Computations comps{xs[0], r, xs};
    auto c = w.RefractedColor(comps, 5);
    EXPECT_EQ(Floats(c), Floats(Color(0, 0, 0)));
}

TEST(WorldTest, RefractedColorAtMaximumRecursiveDepth)
{
    World w = DefaultWorld(DefaultWorldLight, DefaultWorldMaterial1WithRefraction(1.f, 1.5f));
    const Shape *shape = w.Shapes()[0];
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    auto xs = Intersections({{shape, 4}, {shape, 6}});
    Computations comps{xs[0], r, xs};
    auto c = w.RefractedColor(comps, 0);
    EXPECT_EQ(Floats(c), Floats(Color(0, 0, 0)));
}

TEST(WorldTest, RefractedColorUnderTotalInternalReflection)
{
    World w = DefaultWorld(DefaultWorldLight, DefaultWorldMaterial1WithRefraction(1.f, 1.5f));
    const Shape *shape = w.Shapes()[0];
    Ray r{Point(0, 0, HalfSqrt), Vector(0, 1, 0)};
    auto xs = Intersections({{shape, -HalfSqrt}, {shape, HalfSqrt}});
    Computations comps{xs[1], r, xs}; // inside sphere, so 2nd intersections
    auto c = w.RefractedColor(comps, 5);
    EXPECT_EQ(Floats(c), Floats(Color(0, 0, 0)));
}

TEST(WorldTest, RefractedColorWithRefractedRay)
{
    PatternedMaterial m1 = DefaultWorldMaterial1WithAmbientAndPattern(1.f, TestPattern{});
    Material m2 = DefaultWorldMaterial1WithRefraction(1.f, 1.5f);
    World w = DefaultWorld(DefaultWorldLight, m1, m2);

    const Shape *a = w.Shapes()[0];
    const Shape *b = w.Shapes()[1];

    Ray r{Point(0, 0, 0.1f), Vector(0, 1, 0)};
    auto xs = Intersections({{a, -0.9899f}, {b, -0.4899}, {b, 0.4899}, {a, 0.9899f}});
    Computations comps{xs[2], r, xs};
    auto c = w.RefractedColor(comps, 5);
    EXPECT_EQ(Floats(c), Floats(Color(0, 0.99888f, 0.04725f)));
}

TEST(WorldTest, ShadeHitWithTransparentMaterial)
{
    World w = DefaultWorld();
    //Material floorMaterial = Material{};
    //std::unique_ptr<Plane> floor{new Plane{}};
}

} // namespace zrt
