#pragma once

#include "Ray.h"

namespace zrt
{

/// <summary>
/// Camera that (without transform) sits at the origin,
/// looking along negative z, positive y as up-vector.
/// The projection pane is 1 unit away from the camera/eye,
/// that is, at z = -1.
/// </summary>
struct Camera
{
    Camera(unsigned hsize, unsigned vsize, float fov, CXMMATRIX transform = XMMatrixIdentity());

    Ray RayForPixel(unsigned px, unsigned py) const;

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

    inline float PixelSize() const
    {
        return m_pixelSize;
    }

  private:
    unsigned m_hsize;
    unsigned m_vsize;
    float m_fov;
    XMFLOAT4X4 m_transform;
    XMFLOAT4X4 m_inverseTransform;
    float m_halfWidth;
    float m_halfHeight;
    float m_pixelSize;
};

} // namespace zrt
