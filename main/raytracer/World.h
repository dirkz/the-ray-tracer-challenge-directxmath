#pragma once

#include "stdafx.h"

#include "Intersectable.h"
#include "PointLight.h"
#include "Ray.h"

namespace zrt
{

struct World
{
    World();
    World(PointLight light, std::initializer_list<Intersectable *> objects);
    World(World &&world) noexcept;

    std::vector<Intersection> Intersect(const Ray &ray) const;

    inline std::vector<PointLight> Lights() const
    {
        return m_lights;
    }

    inline const std::vector<const Intersectable *> &Objects() const
    {
        return m_objects;
    }

  private:
    std::vector<PointLight> m_lights;
    std::vector<const Intersectable *> m_objects;
    std::vector<std::unique_ptr<const Intersectable *>> m_ownedIntersectables;
};

} // namespace zrt
