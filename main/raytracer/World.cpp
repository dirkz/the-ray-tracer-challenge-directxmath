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

} // namespace zrt