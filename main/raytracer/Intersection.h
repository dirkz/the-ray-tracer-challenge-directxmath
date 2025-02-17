#pragma once

#include "stdafx.h"

#include "Intersectable.h"

namespace zrt
{

struct Intersection
{
    inline Intersection(const Intersectable *pIntersectable, float t)
        : m_intersectable{pIntersectable}, m_t{t} {};

    const Intersectable *Object() const
    {
        return m_intersectable;
    }

    inline float T() const
    {
        return m_t;
    }

  private:
    const Intersectable *m_intersectable;
    float m_t;
};

} // namespace zrt
