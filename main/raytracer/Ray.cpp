#include "Ray.h"

namespace zrt
{

Ray::Ray(FXMVECTOR origin, FXMVECTOR direction)
{
    XMStoreFloat4(&m_origin, origin);
    XMStoreFloat4(&m_direction, direction);
}

} // namespace zrt