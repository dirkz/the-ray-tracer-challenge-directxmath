#include "World.h"

#include "Constants.h"
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

    XMVECTOR overNormal = XMVectorScale(comps.Normal(), Epsilon);
    XMVECTOR overPoint = XMVectorAdd(comps.Point(), overNormal);

    for (const PointLight &light : Lights())
    {
        XMVECTOR lightPosition = light.Position();
        XMVECTOR pointToLightVector = XMVectorSubtract(lightPosition, overPoint);
        Ray lightRay = Ray{overPoint, XMVector4Normalize(pointToLightVector)};
        auto intersections = Intersect(lightRay);
        const Intersection *pNearestIntersection = Hit(intersections);
        bool isInLight = true;
        if (pNearestIntersection)
        {
            float lightDistance = XMVectorGetX(XMVector4Length(pointToLightVector));
            float nearestT = pNearestIntersection->T();
            if (nearestT < lightDistance)
            {
                isInLight = false;
            }
        }

        XMVECTOR c = comps.Object()->Material().Lighting(comps.Object(), light, comps.Point(),
                                                         comps.EyeV(), comps.Normal(), isInLight);
        color = XMVectorAdd(color, c);
    }

    return color;
}

XMVECTOR World::ColorAt(const Ray &ray) const
{
    auto xs = Intersect(ray);
    const Intersection *pI = Hit(xs);

    if (!pI)
    {
        return XMVectorSet(0, 0, 0, 1);
    }

    Computations comps{*pI, ray};
    return ShadeHit(comps);
}

} // namespace zrt