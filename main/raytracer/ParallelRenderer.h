#pragma once

#include "stdafx.h"

#include "Camera.h"
#include "Canvas.h"
#include "World.h"

namespace zrt
{

struct ParallelRenderer
{
    void StartRendering(Canvas &canvas, const World &world, const Camera &camera,
                        unsigned numThreads = std::thread::hardware_concurrency());

  private:
    std::vector<std::thread> m_threads;
};

} // namespace zrt
