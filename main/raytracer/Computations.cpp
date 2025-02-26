#include "Computations.h"

namespace zrt
{

Computations::Computations(const Intersection &i, const Ray &r)
    : m_t{i.T()}, m_pIntersectable{i.Object()}
{
    XMVECTOR point = r.Position(m_t);
    XMStoreFloat4(&m_point, point);

    XMVECTOR direction = r.Direction();
    XMVECTOR eyev = XMVectorScale(direction, -1);
    XMStoreFloat4(&m_eyev, eyev);

    XMVECTOR normal = m_pIntersectable->Normal(point);

    float dotNormalEye = XMVectorGetX(XMVector4Dot(normal, eyev));
    if (dotNormalEye < 0)
    {
        m_inside = true;
        normal = XMVectorScale(normal, -1);
    }
    else
    {
        m_inside = false;
    }

    XMStoreFloat4(&m_normal, normal);

    XMVECTOR reflectv = Reflect(r.Direction(), normal);
    XMStoreFloat4(&m_reflectv, reflectv);
}

} // namespace zrt