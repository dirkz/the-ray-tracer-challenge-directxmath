#include "Ray.h"

#include "Vector.h"

namespace zrt
{

Ray::Ray(FXMVECTOR origin, FXMVECTOR direction)
{
    assert(IsPoint(origin));
    assert(IsVector(direction));
    XMStoreFloat4(&m_origin, origin);
    XMStoreFloat4(&m_direction, direction);
}

} // namespace zrt