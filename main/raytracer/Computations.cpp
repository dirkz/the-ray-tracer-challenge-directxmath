#include "Computations.h"

#include "Constants.h"

namespace zrt
{

Computations::Computations(const Intersection &hit, const Ray &r,
                           std::vector<Intersection> intersections)
    : m_t{hit.T()}, m_pShape{hit.Object()}
{
    XMVECTOR point = r.Position(m_t);
    XMStoreFloat4(&m_point, point);

    XMVECTOR direction = r.Direction();
    XMVECTOR eyev = XMVectorScale(direction, -1);
    XMStoreFloat4(&m_eyev, eyev);

    XMVECTOR normal = m_pShape->Normal(point);

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

    XMVECTOR overNormal = XMVectorScale(normal, Epsilon);
    XMVECTOR overPoint = XMVectorAdd(point, overNormal);
    XMStoreFloat4(&m_overPoint, overPoint);

    XMVECTOR reflectv = Reflect(r.Direction(), normal);
    XMStoreFloat4(&m_reflectv, reflectv);

    std::vector<const Shape *> containers{};
    for (const Intersection &i : intersections)
    {
        if (hit == i)
        {
            if (containers.empty())
            {
                m_n1 = 1.f;
            }
            else
            {
                m_n1 = containers[containers.size() - 1]->Material().RefractiveIndex();
            }
        }

        auto it = std::find(containers.begin(), containers.end(), i.Object());
        if (it != containers.end())
        {
            std::erase(containers, i.Object());
        }
        else
        {
            containers.push_back(i.Object());
        }

        if (hit == i)
        {
            if (containers.empty())
            {
                m_n2 = 1.f;
            }
            else
            {
                m_n2 = containers[containers.size() - 1]->Material().RefractiveIndex();
            }

            break;
        }
    }
}

} // namespace zrt