#pragma once

#include "stdafx.h"

#include "Intersectable.h"
#include "Intersection.h"
#include "Ray.h"

namespace zrt
{

struct Computations
{
    Computations(const Intersection &i, const Ray &r);

  private:
    float m_t;
    const Intersectable *m_pIntersectable;

    XMFLOAT4 m_point;
    XMFLOAT4 m_eyev;
    XMFLOAT4 m_normal;
};

} // namespace zrt
