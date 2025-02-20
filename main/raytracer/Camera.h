#pragma once

#include "stdafx.h"

namespace zrt
{

struct Camera
{
    Camera(unsigned hsize, unsigned vsize, float fov);

    inline unsigned HSize() const
    {
        return m_hsize;
    }

    inline unsigned VSize() const
    {
        return m_vsize;
    }

    inline float Fov() const
    {
        return m_fov;
    }

    inline XMMATRIX XM_CALLCONV Transform() const
    {
        return XMLoadFloat4x4(&m_transform);
    }

  private:
    unsigned m_hsize;
    unsigned m_vsize;
    float m_fov;
    XMFLOAT4X4 m_transform;
};

} // namespace zrt
