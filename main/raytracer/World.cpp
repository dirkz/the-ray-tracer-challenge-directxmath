#include "World.h"

namespace zrt
{

World::World()
{
}

World::World(const PointLight *light, std::initializer_list<Intersectable *> objects)
    : m_light{light}
{
    for (auto intersectable : objects)
    {
        m_ownedIntersectables.push_back(std::make_unique<const Intersectable *>(intersectable));
        m_objects.push_back(intersectable);
    }
}

World::World(World &&world) noexcept : m_light{world.m_light.release()}
{
    m_ownedIntersectables.swap(world.m_ownedIntersectables);
}

} // namespace zrt