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

static World DefaultWorld()
{
    const PointLight *light = new PointLight{Point(-10, 10, -10), Color(1, 1, 1)};

    constexpr float ambient = 0.1f;
    constexpr float diffuse = 0.7f;
    constexpr float specular = 0.2f;
    Material m{Color(0.8f, 1, 0.6f), ambient, diffuse, specular};
    EXPECT_FLOAT_EQ(m.Ambient(), ambient);
    EXPECT_FLOAT_EQ(m.Diffuse(), diffuse);
    EXPECT_FLOAT_EQ(m.Specular(), specular);

    Intersectable *s1 = new Sphere{XMMatrixIdentity(), m};
    Intersectable *s2 = new Sphere{Scaling(0.5f, 0.5f, 0.5f)};

    World w{light, {s1, s2}};

    EXPECT_EQ(w.Light(), light);

    auto itS1 = std::find(w.Objects().begin(), w.Objects().end(), s1);
    auto itS2 = std::find(w.Objects().begin(), w.Objects().end(), s2);

    EXPECT_TRUE(itS1 != w.Objects().end());

    return w;
}

TEST(WorldTest, CreatingWorld)
{
    World w{};
    EXPECT_EQ(w.Light(), nullptr);
    EXPECT_TRUE(w.Objects().empty());
}

TEST(WorldTest, DefaultWorld)
{
    auto w = DefaultWorld();
}

TEST(WorldTest, IntersectWorldRay)
{
    auto w = DefaultWorld();
    auto r = Ray{Point(0, 0, -5), Vector(0, 0, 1)};
    auto xs = w.Intersect(r);
    ASSERT_EQ(xs.size(), 4);
    EXPECT_EQ(xs[0].T(), 4);
    EXPECT_EQ(xs[1].T(), 4.5f);
    EXPECT_EQ(xs[2].T(), 5.5f);
    EXPECT_EQ(xs[3].T(), 6);
}

} // namespace zrt
