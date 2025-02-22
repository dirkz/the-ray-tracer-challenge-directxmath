#include <gtest/gtest.h>

#include "CoordinateProvider.h"

namespace zrt
{

using Coordinate = CoordinateProvider::Coordinate;
using CoordinateLess = CoordinateProvider::Coordinate::Less;

TEST(RenderTest, TraverseAllCoordinates)
{
    constexpr unsigned rows = 2;
    constexpr unsigned cols = 2;

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

    for (unsigned count = 0; count < cols * rows; ++count)
    {
        auto optCoord = provider.Next();
        EXPECT_TRUE(optCoord.has_value());
        if (optCoord.has_value())
        {
            std::cerr << optCoord.value().X() << "," << optCoord.value().Y() << "\n";
			coordinates.insert(optCoord.value());
        }
    }

    EXPECT_FALSE(provider.Next().has_value());
}

} // namespace zrt