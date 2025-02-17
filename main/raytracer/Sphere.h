#pragma once

#include "stdafx.h"

#include "Intersectable.h"

namespace zrt
{

struct Sphere : public Intersectable
{
    std::vector<float> Intersect(const Ray &ray) override;
};

} // namespace zrt
