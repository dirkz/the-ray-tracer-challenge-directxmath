#include "Cylinder.h"

#include "Constants.h"

namespace zrt
{

Cylinder::Cylinder(CXMMATRIX transform, const zrt::Material &material, float minimum, float maximum,
                   bool closed)
    : Shape{transform, material}, m_minimum{minimum}, m_maximum{maximum}, m_closed{closed}
{
}

static bool CheckRay(const Ray &ray, float t)
{
    XMFLOAT4 origin;
    XMStoreFloat4(&origin, ray.Origin());

    XMFLOAT4 direction;
    XMStoreFloat4(&direction, ray.Direction());

    float x = origin.x + t * direction.x;
    float z = origin.z + t * direction.z;

    return (x * x + z * z < 1.f);
}

std::vector<Intersection> Cylinder::LocalIntersect(const Ray &ray) const
{
    XMFLOAT4 origin;
    XMStoreFloat4(&origin, ray.Origin());

    XMFLOAT4 direction;
    XMStoreFloat4(&direction, ray.Direction());

    float a = direction.x * direction.x + direction.z * direction.z;

    if (std::abs(a) < Epsilon)
    {
        return {};
    }

    float b = 2.f * origin.x * direction.x + 2.f * origin.z * direction.z;
    float c = origin.x * origin.x + origin.z * origin.z - 1.f;

    float disc = b * b - 4.f * a * c;

    if (disc < 0)
    {
        return {};
    }

    float t0 = (-b - std::sqrt(disc)) / (2.f * a);
    float t1 = (-b + std::sqrt(disc)) / (2.f * a);

    std::vector<Intersection> xs{};

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

    return xs;
}

XMVECTOR XM_CALLCONV Cylinder::LocalNormal(FXMVECTOR p) const
{
    XMFLOAT4 point;
    XMStoreFloat4(&point, p);

    return Vector(point.x, 0, point.z);
}

} // namespace zrt