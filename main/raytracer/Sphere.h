#pragma once

#include "stdafx.h"

#include "Intersectable.h"

namespace zrt
{

struct Sphere : public Intersectable
{
    using Intersectable::Intersectable;

    std::vector<Intersection> Intersect(const Ray &ray) override;
};

} // namespace zrt
