#pragma once

#include "stdafx.h"

#include "Camera.h"
#include "Canvas.h"
#include "World.h"

namespace zrt
{

struct ParallelRenderer
{
    void StartRendering(Canvas &canvas, const World &world, const Camera &camera);
};

} // namespace zrt
