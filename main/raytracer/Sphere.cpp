#include "Sphere.h"

#include "Vector.h"

namespace zrt
{

std::vector<Intersection> Sphere::Intersect(const Ray &ray)
{
    Ray ray2 = ray.Transform(XMMatrixInverse(nullptr, Transform()));

    // The sphere is at the origin, so the vector to the ray is simply
    // the ray's origin. But we have to set w = 0, hence the subtraction
    // of the origin as a point.
    XMVECTOR sphereToRay = XMVectorSubtract(ray2.Origin(), Point(0, 0, 0));

    float a = DotProduct(ray2.Direction(), ray2.Direction());
    float b = 2 * DotProduct(ray2.Direction(), sphereToRay);
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

        Intersection i1{*this, t1};
        Intersection i2{*this, t2};

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

XMVECTOR XM_CALLCONV Sphere::Normal(FXMVECTOR p)
{
    auto p1 = Floats(p);
    XMVECTOR objectPoint = XMVector4Transform(p, InverseTransform());
    auto p2 = Floats(objectPoint);
    XMVECTOR objectNormal = objectPoint - Point(0);
    auto n1 = Floats(objectNormal);
    XMVECTOR worldNormal = XMVector4Transform(objectNormal, TransposedInverseTransform());
    auto n2 = Floats(worldNormal);
    worldNormal = XMVectorSetW(worldNormal, 0);
    auto n3 = Floats(worldNormal);
    return XMVector3Normalize(worldNormal);
}

} // namespace zrt