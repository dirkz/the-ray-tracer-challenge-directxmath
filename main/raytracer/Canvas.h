#pragma once

#include "stdafx.h"

namespace zrt
{

struct Canvas
{
    Canvas(unsigned width, unsigned height);

    void XM_CALLCONV SetPixel(unsigned x, unsigned y, FXMVECTOR color);
    XMVECTOR XM_CALLCONV GetPixel(unsigned x, unsigned y);

  private:
    unsigned m_width;
    unsigned m_height;
    std::vector<XMFLOAT4> m_pixels;
};

} // namespace zrt
