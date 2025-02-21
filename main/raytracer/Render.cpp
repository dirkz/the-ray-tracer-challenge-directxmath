#include "Render.h"

#include "ParallelRenderer.h"

namespace zrt
{

Canvas RenderParallel(const Camera &camera, const World &world)
{
    Canvas canvas{camera.HSize(), camera.VSize()};

    ParallelRenderer renderer{};
    renderer.StartRendering(canvas, world, camera);
    renderer.Join();

    return canvas;
}

} // namespace zrt