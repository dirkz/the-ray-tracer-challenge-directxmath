#pragma once

#include "stdafx.h"

#include "Camera.h"
#include "Canvas.h"
#include "CoordinateProvider.h"
#include "World.h"

namespace zrt
{

Canvas RenderParallel(const Camera &camera, const World &world);

template <class T> void RenderSequentially(const Camera &camera, const World &world, T &f)
{
    CoordinateProvider provider{camera.HSize(), camera.VSize()};
    while (true)
    {
        auto optCoords = provider.Next();
        if (!optCoords.has_value())
        {
            break;
        }
        unsigned x = optCoords.value().X();
        unsigned y = optCoords.value().Y();
        Ray ray = camera.RayForPixel(x, y);
        auto color = world.ColorAt(ray);
        f(x, y, color);
    }
}

} // namespace zrt
