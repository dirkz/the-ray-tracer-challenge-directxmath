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

    bool haveStillY = m_currentY < m_maxY;
    bool haveStillX = m_currentX < m_maxX;

    if (haveStillX || haveStillY)
    {
        if (haveStillX)
        {
            Coordinate coord = Coordinate{m_currentX, m_currentY};
            ++m_currentX;
            return coord;
        }
        if (haveStillY)
        {
            m_currentX = 0;
            Coordinate coord = Coordinate{m_currentX, m_currentY};
            ++m_currentY;
            return coord;
        }
    }

    return std::optional<Coordinate>{};
}

} // namespace zrt