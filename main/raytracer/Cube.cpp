#include "Cube.h"

namespace zrt
{

std::vector<Intersection> Cube::Intersect(const Ray &ray) const
{
    return {};
}

XMVECTOR XM_CALLCONV Cube::Normal(FXMVECTOR p) const
{
    return XMVectorZero();
}

} // namespace zrt