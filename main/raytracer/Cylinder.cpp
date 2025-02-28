#include "Cylinder.h"

namespace zrt
{

std::vector<Intersection> Cylinder::LocalIntersect(const Ray &ray) const
{
    return {};
}

XMVECTOR XM_CALLCONV Cylinder::Normal(FXMVECTOR p) const
{
    return XMVectorZero();
}

} // namespace zrt