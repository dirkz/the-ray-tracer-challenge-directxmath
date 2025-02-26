#pragma once

#include "Computations.h"
#include "Intersectable.h"
#include "PointLight.h"
#include "Ray.h"

namespace zrt
{

struct World
{
    World();
    World(PointLight light, std::initializer_list<Shape *> objects);
    World(World &&world) noexcept;

    std::vector<Intersection> Intersect(const Ray &ray) const;
    XMVECTOR ShadeHit(const Computations &comps) const;
    XMVECTOR ColorAt(const Ray &ray) const;
    XMVECTOR ReflectedColor(const Computations &comps) const;

    inline std::vector<PointLight> Lights() const
    {
        return m_lights;
    }

    inline const std::vector<const Shape *> &Objects() const
    {
        return m_objects;
    }

  private:
    std::vector<PointLight> m_lights;
    std::vector<const Shape *> m_objects;
    std::vector<std::unique_ptr<const Shape *>> m_ownedIntersectables;
};

} // namespace zrt
