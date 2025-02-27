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

XMVECTOR World::ColorAt(const Ray &ray, unsigned remaining) const
{
    auto intersections = Intersect(ray);
    const Intersection *pI = Hit(intersections);

    if (!pI)
    {
        return XMVectorSet(0, 0, 0, 1);
    }

    Computations comps{*pI, ray, intersections};
    return ShadeHit(comps, remaining);
}

XMVECTOR World::ShadeHit(const Computations &comps, unsigned remaining) const
{
    XMVECTOR surfaceColor = XMVectorZero();

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
        surfaceColor = XMVectorAdd(surfaceColor, c);
    }

    XMVECTOR reflected = ReflectedColor(comps, remaining);

    return XMVectorClamp(surfaceColor + reflected, XMVectorZero(), XMVectorSplatOne());
}

XMVECTOR World::ReflectedColor(const Computations &comps, unsigned remaining) const
{
    if (remaining == 0 || comps.Object()->Material().Reflective() == 0.f)
    {
        return Color(0, 0, 0);
    }

    Ray reflectRay{comps.OverPoint(), comps.ReflectV()};
    XMVECTOR color = ColorAt(reflectRay, remaining - 1);

    return ScaleColor(color, comps.Object()->Material().Reflective());
}

XMVECTOR World::RefractedColor(const Computations &comps, unsigned remaining) const
{
    if (remaining == 0 || comps.Object()->Material().Transparency() == 0.f)
    {
        return Color(0, 0, 0);
    }

    float nRatio = comps.N1() / comps.N2();
    float cosI = XMVectorGetX(XMVector4Dot(comps.EyeV(), comps.Normal()));
    float sinT2 = nRatio * nRatio * (1 - cosI * cosI);

    if (sinT2 > 1.f)
    {
        return Color(0, 0, 0);
    }

    float cosT = std::sqrt(1.f - sinT2);

    XMVECTOR directionPlus = XMVectorScale(comps.Normal(), nRatio * cosI - cosT);
    XMVECTOR directionMinus = XMVectorScale(comps.EyeV(), nRatio);

    XMVECTOR direction = XMVectorSubtract(directionPlus, directionMinus);

    Ray refractedRay{comps.UnderPoint(), direction};

    XMVECTOR colorPure = ColorAt(refractedRay, remaining - 1);
    XMVECTOR colorScaled = XMVectorScale(colorPure, comps.Object()->Material().Transparency());

    return colorScaled;
}

} // namespace zrt