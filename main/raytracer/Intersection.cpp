#include "Intersection.h"

#include "Intersectable.h"

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

bool operator==(const Intersection &s1, const Intersection &s2)
{
    return s1.T() == s2.T() && s1.Object() == s2.Object();
}

bool IntersectionLess::operator()(const Intersection &s1, const Intersection &s2) const
{
    return s1.T() < s2.T();
}

IntersectionList instersections(std::initializer_list<Intersection> intersections)
{
    return std::multiset<Intersection, IntersectionLess>{intersections};
}

const Intersection *hit(const IntersectionList &list)
{
    auto iterator =
        std::find_if(list.begin(), list.end(), [](const Intersection &i) { return i.T() > 0; });

    if (iterator == list.end())
    {
        return nullptr;
    }
    else
    {
        return &(*iterator);
    }
}

} // namespace zrt