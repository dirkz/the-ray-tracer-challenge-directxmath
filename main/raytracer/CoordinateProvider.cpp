#include "CoordinateProvider.h"

namespace zrt
{

CoordinateProvider::CoordinateProvider(unsigned maxX, unsigned maxY)
    : m_maxX{maxX}, m_maxY{maxY}, m_currentX{0}, m_currentY{0}
{
}

std::optional<CoordinateProvider::Coordinate> CoordinateProvider::Next()
{
    std::lock_guard l{m_mutex};

    if (m_currentX == m_maxX - 1 && m_currentY == m_maxY - 1)
    {
        return std::optional<Coordinate>{};
    }

    if (m_currentX < m_maxX)
    {
        Coordinate coord = Coordinate{m_currentX, m_currentY};
        ++m_currentX;
        return coord;
    }

    if (m_currentY < m_maxY)
    {
        m_currentX = 0;
        Coordinate coord = Coordinate{m_currentX, m_currentY};
        ++m_currentY;
        return coord;
    }

    assert(false);
    return std::optional<Coordinate>{};
}

} // namespace zrt