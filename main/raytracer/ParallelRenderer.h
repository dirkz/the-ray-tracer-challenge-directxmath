#pragma once

#include "stdafx.h"

#include "Camera.h"
#include "Canvas.h"
#include "World.h"

namespace zrt
{

struct CoordinateProvider;

struct ParallelRenderer
{
    ParallelRenderer();
    ~ParallelRenderer();

    void StartRendering(Canvas &canvas, const World &world, const Camera &camera,
                        unsigned numThreads = std::thread::hardware_concurrency());
    void Join();

  private:
    std::vector<std::thread> m_threads;
    std::unique_ptr<CoordinateProvider> m_coordinateProvider;
};

} // namespace zrt
