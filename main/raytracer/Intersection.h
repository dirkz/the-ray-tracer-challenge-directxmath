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

std::ostream &operator<<(std::ostream &os, const Intersection &i);

bool operator==(const Intersection &s1, const Intersection &s2);

struct IntersectionLess
{
    bool operator()(const Intersection &s1, const Intersection &s2) const;
};

using IntersectionList = std::multiset<Intersection, IntersectionLess>;

IntersectionList intersections(std::initializer_list<Intersection> intersections);

/// <summary>
/// The first intersection with a distance > 0 from an order list of intersections.
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
const Intersection *hit(const IntersectionList &list);

} // namespace zrt
