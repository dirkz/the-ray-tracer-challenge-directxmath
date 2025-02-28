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
        tmin = tminNumerator * std::numeric_limits<float>::infinity();
        tmax = tmaxNumerator * std::numeric_limits<float>::infinity();
    }

    if (tmin > tmax)
    {
        std::swap(tmin, tmax);
    }

    return {tmin, tmax};
}

template <class T> static inline T max(const T a, const T b, const T c)
{
    return std::max(std::max(a, b), c);
}

template <class T> static inline T min(const T a, const T b, const T c)
{
    return std::min(std::min(a, b), c);
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

    float tmin = max(xtmin, ytmin, ztmin);
    float tmax = min(xtmax, ytmax, ztmax);

    if (tmin > tmax)
    {
        return {};
    }
    else
    {
        return {Intersection{this, tmin}, Intersection{this, tmax}};
    }
}

XMVECTOR XM_CALLCONV Cube::LocalNormal(FXMVECTOR p) const
{
    XMFLOAT4 point;
    XMStoreFloat4(&point, p);

    float x = std::abs(point.x);
    float y = std::abs(point.y);
    float z = std::abs(point.z);

    float maxc = max(x, y, z);

    if (maxc == x)
    {
        return Vector(point.x, 0, 0);
    }
    else if (maxc == y)
    {
        return Vector(0, point.y, 0);
    }
    else
    {
        return Vector(0, 0, point.z);
    }
}

} // namespace zrt