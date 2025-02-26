#include "Shape.h"

namespace zrt
{

Shape::Shape() : Shape(XMMatrixIdentity())
{
}

Shape::Shape(CXMMATRIX transform, const zrt::Material &material) : m_material{material}
{
    XMStoreFloat4x4(&m_transform, transform);
    CreateDerivedTransforms(transform);
}

void XM_CALLCONV Shape::Transform(CXMMATRIX transform)
{
    XMStoreFloat4x4(&m_transform, transform);
    CreateDerivedTransforms(transform);
}

void Shape::CreateDerivedTransforms(CXMMATRIX transform)
{
    XMMATRIX inverse = XMMatrixInverse(nullptr, transform);
    XMStoreFloat4x4(&m_inverseTransform, inverse);
    XMStoreFloat4x4(&m_transposedInverseTransform, XMMatrixTranspose(inverse));
}

bool operator==(const Shape &i1, const Shape &i2)
{
    return &i1 == &i2;
}

} // namespace zrt