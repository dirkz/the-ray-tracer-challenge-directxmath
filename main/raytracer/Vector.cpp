#include "Vector.h"

namespace DirectX
{

std::ostream &XM_CALLCONV operator<<(std::ostream &os, FXMVECTOR v)
{
    XMFLOAT4 floats;
    XMStoreFloat4(&floats, v);

    os << "[" << floats.x << "," << floats.y << "," << floats.z << floats.w << "]";

    return os;
}

void PrintTo(const XMVECTOR &v, ::std::ostream *os)
{
    *os << v;
}

} // namespace DirectX