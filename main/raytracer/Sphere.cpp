#include "Sphere.h"

namespace zrt
{

std::vector<float> Sphere::Intersect(const Ray &ray)
{
    // The sphere is at the origin
    XMVECTOR sphereToRay = ray.Origin();

    XMVECTOR rdDot = XMVector4Dot(ray.Direction(), ray.Direction());
    XMVECTOR b = XMVectorScale(XMVector4Dot(ray.Direction(), sphereToRay), 2);
    XMVECTOR c = XMVectorSubtract(XMVector4Dot(sphereToRay, sphereToRay), XMVectorReplicate(1));

    return std::vector<float>();
}

} // namespace zrt