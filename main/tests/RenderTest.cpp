#include <gtest/gtest.h>

#include "TestConstants.h"
#include "TestUtil.h"

#include "Canvas.h"
#include "CoordinateProvider.h"
#include "Render.h"

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

struct CanvasWriter
{
    CanvasWriter(Canvas &canvas) : m_canvas{canvas} {};
    CanvasWriter(const CanvasWriter &) = delete;

    CanvasWriter &operator=(const CanvasWriter &) = delete;

    void XM_CALLCONV operator()(unsigned x, unsigned y, FXMVECTOR color)
    {
        m_canvas.SetPixel(x, y, color);
    }

  private:
    Canvas &m_canvas;
};

template <class T> void ExecuteRenderTest(const T &fn)
{
    constexpr unsigned rows = 11;
    constexpr unsigned cols = 11;
    Canvas canvas{cols, rows};
    CanvasWriter writer{canvas};

    auto world = DefaultWorld();
    auto from = Point(0, 0, -5);
    auto to = Point(0, 0, 0);
    auto up = Vector(0, 1, 0);
    auto transform = ViewTransform(from, to, up);
    Camera camera{11, 11, HalfPI, transform};

    fn(camera, world, writer);

    auto color = canvas.GetPixel(5, 5);
    EXPECT_EQ(Floats(Color(0.38066f, 0.47583f, 0.2855f)), Floats(color));
}

TEST(RenderTest, RenderSequential)
{
    ExecuteRenderTest([](const Camera &camera, const World &world, CanvasWriter &writer) {
        RenderSequentially(camera, world, writer);
    });
}

TEST(RenderTest, RenderThreaded)
{
    ExecuteRenderTest([](const Camera &camera, const World &world, CanvasWriter &writer) {
        Render(camera, world, 1, writer);
    });
}

} // namespace zrt