#include "Group.h"

namespace zrt
{

std::vector<Intersection> Group::LocalIntersect(const Ray &ray) const
{
    return {};
}

XMVECTOR XM_CALLCONV Group::LocalNormal(FXMVECTOR p) const
{
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