#pragma once

#include "stdafx.h"

namespace zrt
{

struct Intersectable;

struct Intersection
{
    Intersection(const Intersectable *pIntersectable, float t);
    Intersection(const Intersection &other) = default;

    inline const Intersectable *Object() const
    {
        return m_pIntersectable;
    }

    inline float T() const
    {
        return m_t;
    }

    inline Intersection &operator=(const Intersection &other)
    {
        m_pIntersectable = other.m_pIntersectable;
    }

  private:
    const Intersectable *m_pIntersectable;
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
