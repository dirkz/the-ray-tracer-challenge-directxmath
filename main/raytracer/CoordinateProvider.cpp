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

    bool haveStillY = m_currentY < m_maxY - 1;
    bool haveStillX = m_currentX < m_maxX - 1;

    if (haveStillX || haveStillY)
    {
        if (haveStillX)
        {
            ++m_currentX;
            return Coordinate{m_currentX, m_currentY};
        }
        if (haveStillY)
        {
            ++m_currentY;
            m_currentX = 0;
            return Coordinate{m_currentX, m_currentY};
        }
    }

    assert(m_currentX == m_maxX - 1);
    assert(m_currentY == m_maxY - 1);

    return std::optional<Coordinate>{};
}

} // namespace zrt