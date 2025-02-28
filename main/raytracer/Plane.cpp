#include "Plane.h"

#include "Constants.h"
#include "Vector.h"

namespace zrt
{

std::vector<Intersection> Plane::LocalIntersect(const Ray &ray) const
{
    float directionY = XMVectorGetY(ray.Direction());

    if (std::abs(directionY) < Epsilon)
    {
        return {};
    }

    float originY = XMVectorGetY(ray.Origin());

    float t = -originY / directionY;
    Intersection sect{this, t};

    return {sect};
}

XMVECTOR XM_CALLCONV Plane::LocalNormal(FXMVECTOR p) const
{
    return Vector(0, 1, 0);
}

} // namespace zrt