#pragma once

#include "stdafx.h"

#include "Intersection.h"
#include "Ray.h"

namespace zrt
{

struct Intersectable
{
    Intersectable();

    // Can't copy
    Intersectable(const Intersectable &other) = delete;

    // Can't copy
    void operator= (const Intersectable &other) = delete;

    virtual std::vector<Intersection> Intersect(const Ray &ray) = 0;

    /// <summary>
    /// Equality by identity (objects' addresses).
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    bool operator==(const Intersectable &other);
};

} // namespace zrt
