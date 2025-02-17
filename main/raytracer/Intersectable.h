#pragma once

#include "stdafx.h"

#include "Ray.h"

namespace zrt
{

struct Intersectable
{
    virtual std::vector<float> Intersect(const Ray &ray) = 0;
};

} // namespace zrt
