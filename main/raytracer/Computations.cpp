#include "Computations.h"

namespace zrt
{

Computations::Computations(const Intersection &i, const Ray &r)
    : m_t{i.T()}, m_pIntersectable{i.Object()}
{
    XMVECTOR point = r.Position(m_t);
    XMStoreFloat4(&m_point, point);

    XMVECTOR direction = r.Direction();
    XMStoreFloat4(&m_eyev, XMVectorScale(direction, -1));

    XMStoreFloat4(&m_normal, m_pIntersectable->Normal(point));
}

} // namespace zrt