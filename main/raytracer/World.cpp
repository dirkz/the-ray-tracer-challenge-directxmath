#include "World.h"

#include "Intersection.h"

namespace zrt
{

World::World()
{
}

World::World(PointLight light, std::initializer_list<Intersectable *> objects) : m_lights{light}
{
    for (auto intersectable : objects)
    {
        m_ownedIntersectables.push_back(std::make_unique<const Intersectable *>(intersectable));
        m_objects.push_back(intersectable);
    }
}

World::World(World &&world) noexcept : m_lights{world.m_lights}
{
    m_ownedIntersectables.swap(world.m_ownedIntersectables);
}

std::vector<Intersection> World::Intersect(const Ray &ray) const
{
    std::vector<Intersection> intersections{};

    for (const Intersectable *pIntersectable : Objects())
    {
        std::vector<Intersection> objIntersections = pIntersectable->Intersect(ray);
        intersections.insert(intersections.end(), objIntersections.begin(), objIntersections.end());
    }

    std::sort(intersections.begin(), intersections.end(), IntersectionLess{});

    return intersections;
}

XMVECTOR World::ShadeHit(const Computations &comps) const
{
    XMVECTOR color = XMVectorZero();

    for (const PointLight &light : Lights())
    {
        XMVECTOR c =
            comps.Object()->Material().Lighting(light, comps.Point(), comps.EyeV(), comps.Normal());
        color = XMVectorAdd(color, c);
    }

    return color;
}

XMVECTOR World::ColorAt(const Ray &ray)
{
    return XMVectorZero();
}

} // namespace zrt