#include "Plane.h"

#include "Vector.h"

namespace zrt
{

XMVECTOR XM_CALLCONV Plane::Normal(FXMVECTOR p) const
{
    XMVECTOR normal = Vector(0, 1, 0);
    return XMVector4Transform(normal, InverseTransform());
}

} // namespace zrt