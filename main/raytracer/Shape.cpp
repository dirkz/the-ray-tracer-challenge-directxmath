#include "Shape.h"

#include "Group.h"

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

XMVECTOR XM_CALLCONV Shape::WorldToObjectPoint(FXMVECTOR worldPoint) const
{
    if (HasParent())
    {
        XMVECTOR point = m_parent->WorldToObjectPoint(worldPoint);
        return XMVector4Transform(point, InverseTransform());
    }
    else
    {
        return XMVector4Transform(worldPoint, InverseTransform());
    }
}

XMVECTOR XM_CALLCONV Shape::ObjectToWorldNormal(FXMVECTOR objectNormal) const
{
    XMVECTOR worldNormal = XMVector4Transform(objectNormal, TransposedInverseTransform());
    worldNormal = XMVectorSetW(worldNormal, 0);
    worldNormal = XMVector3Normalize(worldNormal);
    if (HasParent())
    {
        return m_parent->ObjectToWorldNormal(worldNormal);
    }
    else
    {
        return worldNormal;
    }
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