#include <gtest/gtest.h>

#include "CoordinateProvider.h"

namespace zrt
{

using Coordinate = CoordinateProvider::Coordinate;
using CoordinateLess = CoordinateProvider::Coordinate::Less;

TEST(RenderTest, TraverseAllCoordinates)
{
    constexpr unsigned rows = 5;
    constexpr unsigned cols = 5;

    std::set<Coordinate, CoordinateLess> coordinates{};

    std::vector<Coordinate> expected{};
    for (unsigned r = 0; r < rows; ++r)
    {
        for (unsigned c = 0; c < cols; ++c)
        {
            expected.emplace_back(c, r);
        }
    }

    CoordinateProvider provider{cols, rows};

    for (unsigned r = 0; r < rows; ++r)
    {
        for (unsigned c = 0; c < cols; ++c)
        {
            auto optCoord = provider.Next();
            std::cerr << r << "," << c << ": " << optCoord.has_value() << "\n";
            ASSERT_TRUE(optCoord.has_value());
            coordinates.insert(optCoord.value());
        }
    }

    EXPECT_FALSE(provider.Next());
}

} // namespace zrt