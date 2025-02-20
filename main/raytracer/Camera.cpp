#include "Camera.h"

namespace zrt
{

Camera::Camera(unsigned hsize, unsigned vsize, float fov)
    : m_hsize{hsize}, m_vsize{vsize}, m_fov{fov}
{
    XMStoreFloat4x4(&m_transform, XMMatrixIdentity());

    float halfView = std::tan(fov / 2.f);
    float aspect = static_cast<float>(hsize) / vsize;
    if (aspect >= 1)
    {
        m_halfWidth = halfView;
        m_halfHeight = halfView / aspect;
    }
    else
    {
        m_halfWidth = halfView * aspect;
        m_halfHeight = halfView;
    }
    m_pixelSize = m_halfWidth * 2.f / static_cast<float>(hsize);
}

} // namespace zrt