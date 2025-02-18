#include "Intersectable.h"

namespace zrt
{

Intersectable::Intersectable() : Intersectable(XMMatrixIdentity())
{
}

Intersectable::Intersectable(CXMMATRIX transform)
{
    XMStoreFloat4x4(&m_transform, transform);
}

void XM_CALLCONV Intersectable::Transform(CXMMATRIX transform)
{
    XMStoreFloat4x4(&m_transform, transform);
}

XMMATRIX XM_CALLCONV Intersectable::Transform()
{
    return XMLoadFloat4x4(&m_transform);
}

bool operator==(const Intersectable &i1, const Intersectable &i2)
{
    return &i1 == &i2;
}

} // namespace zrt