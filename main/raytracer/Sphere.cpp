#include "Sphere.h"

namespace zrt
{

std::vector<float> Sphere::Intersect(const Ray &ray)
{
    // The sphere is at the origin
    XMVECTOR sphereToRay = ray.Origin();

    XMVECTOR va = XMVector4Dot(ray.Direction(), ray.Direction());
    XMFLOAT4 floatsA;
    XMStoreFloat4(&floatsA, va);
    float a = floatsA.x;

    XMVECTOR vDirectionRayDot = XMVector4Dot(ray.Direction(), sphereToRay);
    XMFLOAT4 floatsDirectionRayDot;
    XMStoreFloat4(&floatsDirectionRayDot, vDirectionRayDot);

    float b = 2 * floatsDirectionRayDot.x;

    XMVECTOR vDotSphereToRay = XMVector4Dot(sphereToRay, sphereToRay);
    XMFLOAT4 floatsSphereToRay;
    XMStoreFloat4(&floatsSphereToRay, vDotSphereToRay);

    float c = floatsSphereToRay.x - 1;

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