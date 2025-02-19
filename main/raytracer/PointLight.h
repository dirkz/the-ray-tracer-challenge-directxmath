#pragma once

#include "stdafx.h"

namespace zrt
{

struct PointLight
{
    PointLight(FXMVECTOR position, FXMVECTOR intensity);

    XMVECTOR XM_CALLCONV Position() const
    {
        return XMLoadFloat4(&m_position);
    }

    XMVECTOR XM_CALLCONV Intensity() const
    {
        return XMLoadFloat4(&m_intensity);
    }

  private:
    XMFLOAT4 m_position;
    XMFLOAT4 m_intensity;
};

} // namespace zrt
