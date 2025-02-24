#include "Intersectable.h"

namespace zrt
{

Intersectable::Intersectable() : Intersectable(XMMatrixIdentity())
{
}

Intersectable::Intersectable(CXMMATRIX transform, const zrt::Material &material)
    : m_material{material}
{
    XMStoreFloat4x4(&m_transform, transform);
    CreateDerivedTransforms(transform);
}

void XM_CALLCONV Intersectable::Transform(CXMMATRIX transform)
{
    XMStoreFloat4x4(&m_transform, transform);
    CreateDerivedTransforms(transform);
}

void Intersectable::CreateDerivedTransforms(CXMMATRIX transform)
{
    XMMATRIX inverse = XMMatrixInverse(nullptr, transform);
    XMStoreFloat4x4(&m_inverseTransform, inverse);
    XMStoreFloat4x4(&m_transposedInverseTransform, XMMatrixTranspose(inverse));
}

bool operator==(const Intersectable &i1, const Intersectable &i2)
{
    return &i1 == &i2;
}

} // namespace zrt