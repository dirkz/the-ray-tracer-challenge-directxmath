#include "Camera.h"

namespace zrt
{

Camera::Camera(unsigned hsize, unsigned vsize, float fov)
    : m_hsize{hsize}, m_vsize{vsize}, m_fov{fov}
{
    XMStoreFloat4x4(&m_transform, XMMatrixIdentity());
}

} // namespace zrt