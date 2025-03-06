#include "Shape.h"

namespace zrt
{

Shape::Shape(CXMMATRIX transform, const zrt::Material &material) : m_material{material}, m_parent{}
{
    XMStoreFloat4x4(&m_transform, transform);
    CreateDerivedTransforms(transform);
}

std::vector<Intersection> Shape::Intersect(const Ray &ray) const
{
    Ray ray2 = ray.Transform(InverseTransform());
    return LocalIntersect(ray2);
}

XMVECTOR XM_CALLCONV Shape::Normal(FXMVECTOR worldPoint) const
{
    XMVECTOR point = WorldToObjectPoint(worldPoint);
    XMVECTOR objectNormal = LocalNormal(point);
    return ObjectToWorldNormal(objectNormal);
}

void XM_CALLCONV Shape::Transform(CXMMATRIX transform)
{
    XMStoreFloat4x4(&m_transform, transform);
    CreateDerivedTransforms(transform);
}

void Shape::Parent(Group *group)
{
    m_parent = group;
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