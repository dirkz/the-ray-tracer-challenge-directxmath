#include "Intersection.h"

#include "Intersectable.h"

namespace zrt
{

Intersection::Intersection(const Intersectable *pIntersectable, float t)
    : m_pIntersectable{pIntersectable}, m_t{t}
{
}

std::ostream &operator<<(std::ostream &os, const Intersection &i)
{
    os << "Intersection t=" << i.T() << "\n";
    return os;
}

bool operator==(const Intersection &s1, const Intersection &s2)
{
    return s1.T() == s2.T() && s1.Object() == s2.Object();
}

bool IntersectionLess::operator()(const Intersection &s1, const Intersection &s2) const
{
    return s1.T() < s2.T();
}

std::vector<Intersection> Intersections(std::initializer_list<Intersection> intersections)
{
    std::vector<Intersection> xs{intersections};
    std::sort(xs.begin(), xs.end(), IntersectionLess{});
    return xs;
}

const Intersection *Hit(const std::vector<Intersection> &list)
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