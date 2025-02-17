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

} // namespace zrt