#pragma once

#include "stdafx.h"

namespace zrt
{

struct Canvas
{
    Canvas(unsigned width, unsigned height);

  private:
    unsigned m_width;
    unsigned m_height;
    std::vector<XMFLOAT4> m_pixels;
};

} // namespace zrt
