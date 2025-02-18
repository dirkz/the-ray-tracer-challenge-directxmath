#include "Intersection.h"

namespace zrt
{

Intersection::Intersection(const Intersectable &intersectable, float t)
    : m_intersectable{intersectable}, m_t{t}
{
}

const Intersectable &Intersection::Object() const
{
    return m_intersectable;
}

float Intersection::T() const
{
    return m_t;
}

bool IntersectionLess::operator()(const Intersection &s1, const Intersection &s2) const
{
    return s1.T() < s2.T();
}

std::multiset<Intersection, IntersectionLess> instersections(
    std::initializer_list<Intersection> intersections)
{
    return std::multiset<Intersection, IntersectionLess>{intersections};
}

} // namespace zrt