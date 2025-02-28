#include "Cube.h"

#include "Constants.h"

namespace zrt
{

static std::pair<float, float> CheckAxis(float origin, float direction)
{
    float tmin = 0.f, tmax = 0.f;

    float tminNumerator = -1.f - origin;
    float tmaxNumerator = 1.f - origin;

    if (std::abs(direction) >= Epsilon)
    {
        tmin = tminNumerator / direction;
        tmax = tmaxNumerator / direction;
    }
    else
    {
        tmin = tminNumerator / std::numeric_limits<float>::infinity();
        tmax = tmaxNumerator * std::numeric_limits<float>::infinity();
    }

    if (tmin > tmax)
    {
        std::swap(tmin, tmax);
    }

    return {tmin, tmax};
}

std::vector<Intersection> Cube::LocalIntersect(const Ray &ray) const
{
    XMFLOAT4 origin;
    XMStoreFloat4(&origin, ray.Origin());

    XMFLOAT4 direction;
    XMStoreFloat4(&direction, ray.Direction());

    auto [xtmin, xtmax] = CheckAxis(origin.x, direction.x);
    auto [ytmin, ytmax] = CheckAxis(origin.y, direction.y);
    auto [ztmin, ztmax] = CheckAxis(origin.z, direction.z);

    float tmin = std::max(std::max(xtmin, ytmin), ztmin);
    float tmax = std::min(std::min(xtmax, ytmax), ztmax);

    return {Intersection{this, tmin}, Intersection{this, tmax}};
}

XMVECTOR XM_CALLCONV Cube::Normal(FXMVECTOR p) const
{
    return XMVectorZero();
}

} // namespace zrt