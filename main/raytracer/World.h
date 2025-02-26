#pragma once

#include "Computations.h"
#include "PointLight.h"
#include "Ray.h"
#include "Shape.h"

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

    inline const std::vector<const Shape *> &Shapes() const
    {
        return m_shapes;
    }

  private:
    std::vector<PointLight> m_lights;
    std::vector<const Shape *> m_shapes;
    std::vector<std::unique_ptr<const Shape *>> m_ownedShapes;
};

} // namespace zrt
