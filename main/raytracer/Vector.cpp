#include "Vector.h"

namespace zrt
{

XMFLOAT4 XM_CALLCONV Floats(FXMVECTOR v)
{
    XMFLOAT4 floats;
    XMStoreFloat4(&floats, v);
    return floats;
}

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

bool operator==(const XMFLOAT4 &f1, const XMFLOAT4 &f2)
{
    return f1.x == f2.x && f1.y == f2.y && f1.z == f2.z && f1.w == f2.w;
}

} // namespace DirectX