#pragma once

#include "Intersectable.h"

namespace zrt
{

struct Sphere : public Intersectable
{
    using Intersectable::Intersectable;

    std::vector<Intersection> Intersect(const Ray &ray) const override;
    XMVECTOR XM_CALLCONV Normal(FXMVECTOR p) const override;
};

} // namespace zrt
