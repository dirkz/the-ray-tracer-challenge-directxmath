#include "Group.h"

#include "Intersection.h"

namespace zrt
{

std::vector<Intersection> Group::LocalIntersect(const Ray &ray) const
{
    std::vector<Intersection> hits;

    for (const Shape *s : m_shapes)
    {
        auto xs = s->Intersect(ray);
        hits.insert(hits.end(), xs.begin(), xs.end());
    }

    std::sort(hits.begin(), hits.end(), IntersectionLess{});

    return hits;
}

XMVECTOR XM_CALLCONV Group::LocalNormal(FXMVECTOR p) const
{
    // This should not get called.
    assert(false);

    return XMVectorZero();
}

bool Group::Empty() const
{
    return m_shapes.empty();
}

void Group::Add(Shape *shape)
{
    m_shapes.push_back(shape);
    shape->Parent(this);
}

bool Group::Contains(const Shape *shape) const
{
    for (const auto *s : m_shapes)
    {
        if (s == shape)
        {
            return true;
        }
    }
    return false;
}

} // namespace zrt