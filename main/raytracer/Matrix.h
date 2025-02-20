#pragma once

namespace zrt
{

inline XMMATRIX XM_CALLCONV Translation(float x, float y, float z)
{
    return XMMatrixTranslation(x, y, z);
}

inline XMMATRIX XM_CALLCONV Scaling(float x, float y, float z)
{
    return XMMatrixScaling(x, y, z);
}

inline XMMATRIX XM_CALLCONV RotationX(float angle)
{
    return XMMatrixRotationX(angle);
}

inline XMMATRIX XM_CALLCONV RotationY(float angle)
{
    return XMMatrixRotationY(angle);
}

inline XMMATRIX XM_CALLCONV RotationZ(float angle)
{
    return XMMatrixRotationZ(angle);
}

XMMATRIX XM_CALLCONV ViewTransform(FXMVECTOR from, FXMVECTOR to, FXMVECTOR up);

} // namespace zrt
