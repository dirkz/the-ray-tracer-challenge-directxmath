#include "ParallelRenderer.h"

namespace zrt
{

namespace parallel
{

using Coordinate = std::optional<std::pair<unsigned, unsigned>>;

struct CoordinateProvider
{
    CoordinateProvider(unsigned maxX, unsigned maxY)
        : m_maxX{maxX}, m_maxY{maxY}, m_currentX{0}, m_currentY{0}
    {
    }

    ~CoordinateProvider() = default;

    Coordinate Next()
    {
        std::lock_guard lock{m_mutex};

        if (m_currentX < m_maxX)
        {
            m_currentX++;
        }
        else if (m_currentY < m_maxY)
        {
            m_currentY++;
            m_currentX = 0;
        }

        if (m_currentX < m_maxX && m_currentY < m_maxY)
        {
            auto pair = std::make_pair(m_currentX, m_currentY);
            return std::make_optional(pair);
        }
        else
        {
            return Coordinate{};
        }
    }

  private:
    unsigned m_maxX;
    unsigned m_maxY;
    std::mutex m_mutex;
    unsigned m_currentX;
    unsigned m_currentY;
};

static void Render(Canvas &canvas, const World &world, const Camera &camera,
                   CoordinateProvider *pCoordinateProvider)
{
    while (true)
    {
        Coordinate coordinate = pCoordinateProvider->Next();
        if (!coordinate.has_value())
        {
            return;
        }
        else
        {
            unsigned x = coordinate.value().first;
            unsigned y = coordinate.value().second;
            Ray ray = camera.RayForPixel(x, y);
            auto color = world.ColorAt(ray);
            canvas.SetPixel(x, y, color);
        }
    }
}

struct RenderFunctor
{
    RenderFunctor(Canvas &canvas, const World &world, const Camera &camera,
                  CoordinateProvider *pCoordinateProvider)
        : m_canvas{canvas}, m_world{world}, m_camera{camera},
          m_coordinateProvider{pCoordinateProvider}
    {
    }

    void operator()()
    {
        Render(m_canvas, m_world, m_camera, m_coordinateProvider);
    }

  private:
    Canvas &m_canvas;
    const World &m_world;
    const Camera &m_camera;
    CoordinateProvider *m_coordinateProvider;
};

} // namespace parallel

ParallelRenderer::ParallelRenderer()
{
}

ParallelRenderer::~ParallelRenderer() = default;

void ParallelRenderer::StartRendering(Canvas &canvas, const World &world, const Camera &camera,
                                      unsigned numThreads)
{
    m_threads.clear();

    if (numThreads == 0)
    {
        numThreads = 2;
    }

    m_coordinateProvider.reset(new parallel::CoordinateProvider{canvas.Height(), canvas.Width()});

    for (unsigned i = 0; i < numThreads; ++i)
    {
        parallel::RenderFunctor f{canvas, world, camera, m_coordinateProvider.get()};
        std::thread thread{f};
        m_threads.push_back(std::move(thread));
    }
}

void ParallelRenderer::Join()
{
    for (std::thread &t : m_threads)
    {
        t.join();
    }
}

} // namespace zrt