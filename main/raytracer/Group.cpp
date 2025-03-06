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
    return m_children.empty();
}

void Group::Add(Shape *shape)
{
    m_children.push_back(shape);
    shape->Parent(this);
}

} // namespace zrt