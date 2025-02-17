#pragma once

#include "stdafx.h"

namespace zrt
{

struct Intersectable;

struct Intersection
{
    Intersection(const Intersectable &intersectable, float t);

    const Intersectable &Object() const;
    float T() const;

  private:
    const Intersectable &m_intersectable;
    float m_t;
};

} // namespace zrt
