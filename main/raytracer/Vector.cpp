#include "Vector.h"

namespace zrt
{

std::ostream &XM_CALLCONV operator<<(std::ostream &os, FXMVECTOR v)
{
    XMFLOAT4 floats;
    XMStoreFloat4(&floats, v);

    os << "[" << floats.x << "," << floats.y << "," << floats.z << floats.w << "]";

    return os;
}

} // namespace zrt

namespace DirectX
{

std::ostream &operator<<(std::ostream &os, const XMFLOAT4 &f)
{
    os << "[" << f.x << "," << f.y << "," << f.z << "," << f.w << "]";
    return os;
}

} // namespace DirectX