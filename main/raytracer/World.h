#pragma once

#include "stdafx.h"

#include "Intersectable.h"
#include "PointLight.h"

namespace zrt
{

struct World
{
    World();
    World(const PointLight *light, std::initializer_list<Intersectable *> objects);
    World(World &&world) noexcept;

    inline const PointLight *Light() const
    {
        return m_light.get();
    }

    inline const std::vector<const Intersectable *> &Objects() const
    {
        return m_objects;
    }

  private:
    std::unique_ptr<const PointLight> m_light;
    std::vector<const Intersectable *> m_objects;
    std::vector<std::unique_ptr<const Intersectable *>> m_ownedIntersectables;
};

} // namespace zrt
