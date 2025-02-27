#pragma once

#include "stdafx.h"

#include "Camera.h"
#include "Canvas.h"
#include "CoordinateProvider.h"
#include "Material.h"
#include "Matrix.h"
#include "Pattern.h"
#include "Plane.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Vector.h"
#include "World.h"

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

template <class T>
void Render(const Camera &camera, const World &world, unsigned maxNumberOfReflections,
            T &setPixelFn)
{
    unsigned numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0 || numThreads == 1)
    {
        RenderSequentially(camera, world, setPixelFn);
    }
    else
    {
        if (numThreads > 4)
        {
            numThreads -= 2;
        }
        else if (numThreads > 1)
        {
            numThreads--;
        }

        CoordinateProvider provider{camera.HSize(), camera.VSize()};

        auto renderFn = [&provider, &camera, &world, maxNumberOfReflections, &setPixelFn]() {
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
                auto color = world.ColorAt(ray, maxNumberOfReflections);
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
