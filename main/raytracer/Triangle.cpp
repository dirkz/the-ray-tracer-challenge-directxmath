#include "Triangle.h"

#include "Constants.h"

namespace zrt
{

Triangle::Triangle(FXMVECTOR p1, FXMVECTOR p2, FXMVECTOR p3, CXMMATRIX transform,
                   const zrt::Material &material)
    : Shape{transform, material}
{
    XMStoreFloat4(&m_p1, p1);
    XMStoreFloat4(&m_p2, p2);
    XMStoreFloat4(&m_p3, p3);

    // From P1 to P2 (P2 - P1).
    XMVECTOR e1 = XMVectorSubtract(p2, p1);
    XMStoreFloat4(&m_e1, e1);

    // From P1 to P3 (P3 - P1).
    XMVECTOR e2 = XMVectorSubtract(p3, p1);
    XMStoreFloat4(&m_e2, e2);

    XMVECTOR normal = XMVector3Cross(e2, e1);
    normal = XMVector3Normalize(normal);
    XMStoreFloat4(&m_normal, normal);
}

std::vector<Intersection> Triangle::LocalIntersect(const Ray &ray) const
{
    XMVECTOR dirCrossE2 = XMVector3Cross(ray.Direction(), E2());
    XMVECTOR detv = XMVector3Dot(E1(), dirCrossE2);
    float det = XMVectorGetX(detv);

    if (std::abs(det) < Epsilon)
    {
        return {};
    }

    float f = 1.f / det;

    XMVECTOR p1ToOrigin = XMVectorSubtract(ray.Origin(), P1());
    XMVECTOR dotv = XMVector3Dot(p1ToOrigin, dirCrossE2);
    float dot = XMVectorGetX(dotv);
    float u = f * dot;

    if (u < 0 || u > 1)
    {
        return {};
    }

    XMVECTOR originCrossE1 = XMVector3Cross(p1ToOrigin, E1());
    XMVECTOR vv = XMVector3Dot(ray.Direction(), originCrossE1);
    float v = XMVectorGetX(vv) * f;

    if (v < 0 || (u + v) > 1)
    {
        return {};
    }

    XMVECTOR dotv2 = XMVector3Dot(E2(), originCrossE1);
    float t = XMVectorGetX(dotv2) * f;

    return {Intersection{this, t}};
}

XMVECTOR XM_CALLCONV Triangle::LocalNormal(FXMVECTOR p) const
{
    return XMLoadFloat4(&m_normal);
}

} // namespace zrt