#pragma once

#include "stdafx.h"

namespace zrt
{

/// <summary>
/// Generates all 2d coordinates on a given plane and provides access to them
/// in a thread-safe manner.
/// </summary>
struct CoordinateProvider
{
    struct Coordinate
    {
        struct Less
        {
            bool operator()(const Coordinate &c1, const Coordinate &c2) const
            {
                return c1.X() < c2.X() && c1.Y() < c2.Y();
            };
        };

        Coordinate(unsigned x, unsigned y) : m_x{x}, m_y{y} {};

        inline unsigned X() const
        {
            return m_x;
        }

        inline unsigned Y() const
        {
            return m_y;
        }

      private:
        unsigned m_x;
        unsigned m_y;
    };

    CoordinateProvider(unsigned maxX, unsigned maxY);

    /// <summary>
    /// Thread-safe access to the next available coordinate, or nothing, if all work has been done.
    /// </summary>
    /// <returns></returns>
    std::optional<Coordinate> Next();

  private:
    unsigned m_maxX;
    unsigned m_maxY;
    std::mutex m_mutex;
    unsigned m_currentX;
    unsigned m_currentY;
};

} // namespace zrt
