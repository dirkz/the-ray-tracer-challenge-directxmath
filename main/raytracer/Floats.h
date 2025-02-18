#pragma once

#include "stdafx.h"

namespace zrt
{

constexpr float Epsilon = 0.0001f;

inline bool IsEqual(float f1, float f2)
{
    return abs(f1 - f2) < Epsilon;
}

} // namespace zrt
