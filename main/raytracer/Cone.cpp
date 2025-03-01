#include "Cone.h"

#include "Constants.h"

namespace zrt
{

Cone::Cone(CXMMATRIX transform, const zrt::Material &material, float minimum, float maximum,
           bool closed)
    : Shape{transform, material}, m_minimum{minimum}, m_maximum{maximum}, m_closed{closed}
{
}

std::vector<Intersection> Cone::LocalIntersect(const Ray &ray) const
{
    XMFLOAT4 direction;
    XMStoreFloat4(&direction, ray.Direction());

    XMFLOAT4 origin;
    XMStoreFloat4(&origin, ray.Origin());

    float a = direction.x * direction.x - direction.y * direction.y + direction.z * direction.z;

    float b =
        2.f * origin.x * direction.x - 2.f * origin.y * direction.y + 2.f * origin.z * direction.z;

    float c = origin.x * origin.x - origin.y * origin.y + origin.z * origin.z;

    if (std::abs(a) < Epsilon)
    {
        if (std::abs(b) >= Epsilon)
        {
            float t = -c / (2.f * b);
            return {Intersection{this, t}};
        }
        else
        {
            return {};
        }
    }

    std::vector<Intersection> xs{};

    float disc = b * b - 4.f * a * c;

    if (disc < 0)
    {
        if (std::abs(disc) >= Epsilon)
        {
            return {};
        }
        else
        {
            disc = 0.f;
        }
    }

    float t0 = (-b - std::sqrt(disc)) / (2.f * a);
    float t1 = (-b + std::sqrt(disc)) / (2.f * a);

    float y0 = origin.y + t0 * direction.y;

    if (m_minimum < y0 && y0 < m_maximum)
    {
        xs.push_back(Intersection{this, t0});
    }

    float y1 = origin.y + t1 * direction.y;

    if (m_minimum < y1 && y1 < m_maximum)
    {
        xs.push_back(Intersection{this, t1});
    }

    IntersectCaps(ray, xs);

    return xs;
}

XMVECTOR XM_CALLCONV Cone::LocalNormal(FXMVECTOR p) const
{
    XMFLOAT4 point;
    XMStoreFloat4(&point, p);

    float dist = point.x * point.x + point.z * point.z;
    if (dist < 1.f)
    {
        if (point.y >= m_maximum - Epsilon)
        {
            return Vector(0, 1, 0);
        }
        else if (point.y <= m_minimum + Epsilon)
        {
            return Vector(0, -1, 0);
        }
    }

    return Vector(point.x, 0, point.z);
}

static bool CheckCap(const Ray &ray, float t, float y)
{
    XMVECTOR scaled = XMVectorScale(ray.Direction(), t);
    XMVECTOR p = XMVectorAdd(ray.Origin(), scaled);

    XMFLOAT4 point;
    XMStoreFloat4(&point, p);

    float x2 = point.x * point.x;
    float z2 = point.z * point.z;

    return (x2 + z2) <= y + Epsilon;
}

void Cone::IntersectCaps(const Ray &ray, std::vector<Intersection> &xs) const
{
    if (!m_closed)
    {
        return;
    }

    XMFLOAT4 direction;
    XMStoreFloat4(&direction, ray.Direction());

    if (std::abs(direction.y) < Epsilon)
    {
        return;
    }

    XMFLOAT4 origin;
    XMStoreFloat4(&origin, ray.Origin());

    float t = (m_minimum - origin.y) / direction.y;
    if (CheckCap(ray, t, m_minimum))
    {
        xs.push_back({Intersection{this, t}});
    }

    t = (m_maximum - origin.y) / direction.y;
    if (CheckCap(ray, t, m_maximum))
    {
        xs.push_back({Intersection{this, t}});
    }
}

} // namespace zrt