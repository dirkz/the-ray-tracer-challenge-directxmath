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

} // namespace zrt
