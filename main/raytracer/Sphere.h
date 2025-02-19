#pragma once

#include "stdafx.h"

#include "Intersectable.h"

namespace zrt
{

struct Sphere : public Intersectable
{
    using Intersectable::Intersectable;

    std::vector<Intersection> Intersect(const Ray &ray) const override;
    XMVECTOR XM_CALLCONV Normal(FXMVECTOR p) override;
};

} // namespace zrt
