#include "ParallelRenderer.h"

namespace zrt
{

using Coordinate = std::optional<std::pair<unsigned, unsigned>>;

struct CoordinateProvider
{
    CoordinateProvider(unsigned maxX, unsigned maxY)
        : m_maxX{maxX}, m_maxY{maxY}, m_currentX{0}, m_currentY{0}
    {
    }

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

void ParallelRenderer::StartRendering(Canvas &canvas, const World &world, const Camera &camera)
{
}

} // namespace zrt