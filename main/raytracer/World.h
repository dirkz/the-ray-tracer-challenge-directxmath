#pragma once

#include "stdafx.h"

#include "PointLight.h"

class Intersectable;

namespace zrt
{

struct World
{
    World();
    World(const PointLight *light, std::initializer_list<const Intersectable *> objects);

    inline const PointLight *Light() const
    {
        return m_light.get();
    }

    inline const std::vector<std::unique_ptr<const Intersectable *>> &Objects() const
    {
        return m_objects;
    }

  private:
    std::unique_ptr<const PointLight> m_light;
    std::vector<std::unique_ptr<const Intersectable *>> m_objects;
};

} // namespace zrt
