#include "World.h"

#include "Constants.h"
#include "Intersection.h"

namespace zrt
{

World::World()
{
}

World::World(PointLight light, std::initializer_list<Shape *> shapes) : m_lights{light}
{
    for (auto shape : shapes)
    {
        m_ownedShapes.push_back(std::make_unique<const Shape *>(shape));
        m_shapes.push_back(shape);
    }
}

World::World(World &&world) noexcept : m_lights{world.m_lights}
{
    m_ownedShapes.swap(world.m_ownedShapes);
}

void World::Add(const Shape *shape)
{
    m_ownedShapes.push_back(std::make_unique<const Shape *>(shape));
    m_shapes.push_back(shape);
}

std::vector<Intersection> World::Intersect(const Ray &ray) const
{
    std::vector<Intersection> intersections{};

    for (const Shape *pShape : Shapes())
    {
        std::vector<Intersection> objIntersections = pShape->Intersect(ray);
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
        XMVECTOR lightPosition = light.Position();
        XMVECTOR pointToLightVector = XMVectorSubtract(lightPosition, comps.OverPoint());
        Ray lightRay = Ray{comps.OverPoint(), XMVector4Normalize(pointToLightVector)};
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

XMVECTOR World::ReflectedColor(const Computations &comps) const
{
    if (comps.Object()->Material().Reflective() == 0.f)
    {
        return Color(0, 0, 0);
    }

    return XMVECTOR();
}

} // namespace zrt