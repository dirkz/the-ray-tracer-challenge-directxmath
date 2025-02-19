#pragma once

#include "stdafx.h"

#include "PointLight.h"

class Intersectable;

namespace zrt
{

struct World
{
    World();

  private:
    std::unique_ptr<PointLight> m_light;
    std::vector<Intersectable *> m_objects;
};

} // namespace zrt
