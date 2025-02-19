#include "World.h"

namespace zrt
{

World::World()
{
}

World::World(const PointLight *light, std::initializer_list<const Intersectable *> objects)
    : m_light{light}
{
    for (auto intersectable : objects)
    {
        m_objects.push_back(std::make_unique<const Intersectable *>(intersectable));
    }
}

} // namespace zrt