#include <gtest/gtest.h>

#include "Material.h"
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

} // namespace zrt
