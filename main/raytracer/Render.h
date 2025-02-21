#pragma once

#include "stdafx.h"

#include "Camera.h"
#include "Canvas.h"
#include "World.h"

namespace zrt
{

Canvas RenderParallel(const Camera &camera, const World &world);

}
