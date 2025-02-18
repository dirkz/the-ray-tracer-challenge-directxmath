#pragma once

#include "stdafx.h"

namespace zrt
{

inline XMMATRIX Translation(float x, float y, float z)
{
    return XMMatrixTranslation(x, y, z);
}

inline XMMATRIX Scaling(float x, float y, float z)
{
    return XMMatrixScaling(x, y, z);
}

inline XMMATRIX RotationX(float angle)
{
    return XMMatrixRotationX(angle);
}

inline XMMATRIX RotationY(float angle)
{
    return XMMatrixRotationY(angle);
}

inline XMMATRIX RotationZ(float angle)
{
    return XMMatrixRotationZ(angle);
}

} // namespace zrt
