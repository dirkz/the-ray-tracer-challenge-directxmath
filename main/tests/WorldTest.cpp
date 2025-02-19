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

static void DefaultWorld()
{
    auto light = new PointLight{Point(-10, 10, -10), Color(1, 1, 1)};

    constexpr float ambient = 0.1f;
    constexpr float diffuse = 0.7f;
    constexpr float specular = 0.2f;
    Material m{Color(0.8f, 1, 0.6f), ambient, diffuse, specular};
    EXPECT_FLOAT_EQ(m.Ambient(), ambient);
    EXPECT_FLOAT_EQ(m.Diffuse(), diffuse);
    EXPECT_FLOAT_EQ(m.Specular(), specular);

    auto s1 = new Sphere{XMMatrixIdentity(), m};
    auto s2 = new Sphere{Scaling(0.5f, 0.5f, 0.5f)};

    World w{light, {s1, s2}};
}

TEST(WorldTest, CreatingWorld)
{
    World w{};
    EXPECT_EQ(w.Light(), nullptr);
    EXPECT_TRUE(w.Objects().empty());
}

} // namespace zrt
