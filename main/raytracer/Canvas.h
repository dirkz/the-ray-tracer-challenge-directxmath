#pragma once

#include "stdafx.h"

namespace zrt
{

struct Canvas
{
    Canvas(unsigned width, unsigned height);

    Canvas(const Canvas &) = delete;
    Canvas &operator=(const Canvas &) = delete;

    void XM_CALLCONV SetPixel(unsigned x, unsigned y, FXMVECTOR color);
    XMVECTOR XM_CALLCONV GetPixel(unsigned x, unsigned y);

    inline unsigned Width() const
    {
        return m_width;
    }

    inline unsigned Height() const
    {
        return m_height;
    }

  private:
    unsigned m_width;
    unsigned m_height;
    std::vector<XMFLOAT4> m_pixels;
};

} // namespace zrt
