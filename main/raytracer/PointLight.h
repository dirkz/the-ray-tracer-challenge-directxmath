#pragma once

#include "stdafx.h"

namespace zrt
{

struct PointLight
{
    PointLight(FXMVECTOR position, FXMVECTOR intensity);

    XMVECTOR XM_CALLCONV Position();
    XMVECTOR XM_CALLCONV Intensity();

  private:
    XMFLOAT4 m_position;
    XMFLOAT4 m_intensity;
};

} // namespace zrt
