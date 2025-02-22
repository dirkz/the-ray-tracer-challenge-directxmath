#pragma once

#include "stdafx.h"

#include "Camera.h"
#include "Canvas.h"
#include "CoordinateProvider.h"
#include "World.h"
#include "Matrix.h"

namespace zrt
{

template <class T> void RenderSequentially(const Camera &camera, const World &world, T &f)
{
    for (unsigned y = 0; y < camera.VSize(); ++y)
    {
        for (unsigned x = 0; x < camera.HSize(); ++x)
        {
            Ray ray = camera.RayForPixel(x, y);
            auto color = world.ColorAt(ray);
            f(x, y, color);
        }
    }
}

template <class T> void Render(const Camera &camera, const World &world, T &setPixelFn)
{
    unsigned numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0)
    {
        RenderSequentially(camera, world, setPixelFn);
    }
    else
    {
        CoordinateProvider provider{camera.HSize(), camera.VSize()};

        auto renderFn = [&provider, &camera, &world, &setPixelFn]() {
            while (true)
            {
                auto optCoords = provider.Next();
                if (!optCoords.has_value())
                {
                    return;
                }
                unsigned x = optCoords.value().X();
                unsigned y = optCoords.value().Y();
                Ray ray = camera.RayForPixel(x, y);
                auto color = world.ColorAt(ray);
                setPixelFn(x, y, color);
            }
        };

        std::vector<std::thread> threads(numThreads);
        for (unsigned i = 0; i < numThreads; ++i)
        {
            std::thread thread{renderFn};
            threads[i] = std::move(thread);
        }

        for (std::thread &thread : threads)
        {
            thread.join();
        }
    }
}

} // namespace zrt
