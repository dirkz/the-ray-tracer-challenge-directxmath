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

void XM_CALLCONV Canvas::SetPixel(unsigned x, unsigned y, FXMVECTOR color)
{
    XMVECTOR clampedColor = XMVectorClamp(color, XMVectorZero(), XMVectorSplatOne());
    XMStoreFloat4(&m_pixels[y * m_width + x], clampedColor);
}

XMVECTOR XM_CALLCONV Canvas::GetPixel(unsigned x, unsigned y)
{
    return XMLoadFloat4(&m_pixels[y * m_width + x]);
}

} // namespace zrt