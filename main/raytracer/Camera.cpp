#include "Camera.h"

#include "Vector.h"

namespace zrt
{

Camera::Camera(unsigned hsize, unsigned vsize, float fov, CXMMATRIX transform)
    : m_hsize{hsize}, m_vsize{vsize}, m_fov{fov}
{
    XMStoreFloat4x4(&m_transform, transform);
    XMStoreFloat4x4(&m_inverseTransform, XMMatrixInverse(nullptr, transform));

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

Ray Camera::RayForPixel(unsigned px, unsigned py) const
{
    float offsetX = (static_cast<float>(px) + 0.5f) * m_pixelSize;
    float offsetY = (static_cast<float>(py) + 0.5f) * m_pixelSize;

    float worldY = m_halfHeight - offsetY;
    float worldX = m_halfWidth - offsetX;

    XMVECTOR pointOnCanvas = Point(worldX, worldY, -1);

    XMVECTOR pixel = XMVector4Transform(pointOnCanvas, XMLoadFloat4x4(&m_inverseTransform));
    XMVECTOR origin = XMVector4Transform(Vector(0, 0, 0), XMLoadFloat4x4(&m_inverseTransform));
    origin = XMVectorSetW(origin, 1);

    XMVECTOR direction = XMVectorSubtract(pixel, origin);
    direction = XMVector3Normalize(direction);

    return Ray{origin, direction};
}

} // namespace zrt