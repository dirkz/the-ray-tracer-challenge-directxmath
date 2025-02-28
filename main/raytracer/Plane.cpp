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

XMVECTOR XM_CALLCONV Plane::Normal(FXMVECTOR p) const
{
    XMVECTOR normal = Vector(0, 1, 0);
    XMVECTOR transposed = XMVector4Transform(normal, TransposedInverseTransform());
    transposed = XMVectorSetW(transposed, 0.f);
    return transposed;
}

} // namespace zrt