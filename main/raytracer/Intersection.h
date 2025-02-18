#pragma once

#include "stdafx.h"

namespace zrt
{

struct Intersectable;

struct Intersection
{
    Intersection(const Intersectable &intersectable, float t);
    Intersection(const Intersection &other) = default;

    const Intersectable &Object() const;
    float T() const;

  private:
    const Intersectable &m_intersectable;
    float m_t;
};

bool operator==(const Intersection &s1, const Intersection &s2);

struct IntersectionLess
{
    bool operator()(const Intersection &s1, const Intersection &s2) const;
};

using IntersectionList = std::multiset<Intersection, IntersectionLess>;

IntersectionList instersections(std::initializer_list<Intersection> intersections);

} // namespace zrt
