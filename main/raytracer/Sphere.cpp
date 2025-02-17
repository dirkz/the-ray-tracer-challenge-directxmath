#include "Sphere.h"

#include "Tuple.h"

namespace zrt
{

std::vector<float> Sphere::Intersect(const Ray &ray)
{
    // The sphere is at the origin
    XMVECTOR sphereToRay = ray.Origin();

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

        if (t1 < t2)
        {
            return {t1, t2};
        }
        else
        {
            return {t2, t1};
        }
    }
}

} // namespace zrt