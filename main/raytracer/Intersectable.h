#pragma once

#include "stdafx.h"

#include "Ray.h"
#include "Intersection.h"

namespace zrt
{

struct Intersectable
{
    virtual std::vector<Intersection> Intersect(const Ray &ray) = 0;
};

} // namespace zrt
