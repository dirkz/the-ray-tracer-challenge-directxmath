#include "Canvas.h"

#include "Vector.h"

namespace zrt
{

Canvas::Canvas(unsigned width, unsigned height)
    : m_width{width}, m_height{height}, m_pixels(width * height)
{
    for (unsigned x = 0; x < width; ++x)
    {
        for (unsigned y = 0; y < height; ++y)
        {
            XMStoreFloat4(&m_pixels[y * width + x], Color(0, 0, 0));
        }
    }
}

} // namespace zrt