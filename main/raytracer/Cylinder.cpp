#include "Cylinder.h"

#include "Constants.h"

namespace zrt
{

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

    // dummy
    return {Intersection{this, 1.f}};
}

XMVECTOR XM_CALLCONV Cylinder::Normal(FXMVECTOR p) const
{
    return XMVectorZero();
}

} // namespace zrt