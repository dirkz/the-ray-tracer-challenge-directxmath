#include "Sphere.h"

#include "Vector.h"

namespace zrt
{

std::vector<Intersection> Sphere::LocalIntersect(const Ray &ray) const
{
    // The sphere is at the origin, so the vector to the ray is simply
    // the ray's origin. But we have to set w = 0, hence the subtraction
    // of the origin as a point.
    XMVECTOR sphereToRay = XMVectorSubtract(ray.Origin(), Point(0, 0, 0));

    float a = DotProduct(ray.Direction(), ray.Direction());
    float b = 2 * DotProduct(ray.Direction(), sphereToRay);
    float c = DotProduct(sphereToRay, sphereToRay) - 1;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return {};
    }
    else
    {
        float rootD = sqrt(discriminant);
        float t1 = (-b - rootD) / (2 * a);
        float t2 = (-b + rootD) / (2 * a);

        Intersection i1{this, t1};
        Intersection i2{this, t2};

        if (t1 < t2)
        {
            return {i1, i2};
        }
        else
        {
            return {i2, i1};
        }
    }
}

XMVECTOR XM_CALLCONV Sphere::LocalNormal(FXMVECTOR p) const
{
    return XMVectorSubtract(p, Point());
}

} // namespace zrt