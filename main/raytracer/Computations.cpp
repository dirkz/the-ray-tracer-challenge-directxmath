#include "Computations.h"

#include "Constants.h"

namespace zrt
{

Computations::Computations(const Intersection &hit, const Ray &r,
                           const std::vector<Intersection> &intersections)
    : m_t{hit.T()}, m_pShape{hit.Object()}, m_n1{0.f}, m_n2{0.f}
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

    XMVECTOR underNormal = XMVectorScale(normal, -Epsilon);
    XMVECTOR underPoint = XMVectorAdd(point, underNormal);
    XMStoreFloat4(&m_underPoint, underPoint);

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

float Computations::Schlick() const
{
    float cosine = XMVectorGetX(XMVector3Dot(EyeV(), Normal()));

    if (N1() > N2())
    {
        float n = N1() / N2();
        float sin2T = n * n * (1.f - cosine * cosine);
        if (sin2T > 1.f)
        {
            return 1.f;
        }

        float cosT = std::sqrt(1.f - sin2T);
        cosine = cosT;
    }

    float r0a = (N1() - N2()) / (N1() + N2());
    float r0 = r0a * r0a;

    return r0 + (1.f - r0) * std::pow(1.f - cosine, 5.f);
}

} // namespace zrt