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

    XMVECTOR vb = XMVectorScale(XMVector4Dot(ray.Direction(), sphereToRay), 2);
    XMFLOAT4 floatsB;
    XMStoreFloat4(&floatsB, vb);
    float b = floatsB.x;

    XMVECTOR vc = XMVectorSubtract(XMVector4Dot(sphereToRay, sphereToRay), XMVectorReplicate(1));
    XMFLOAT4 floatsC;
    XMStoreFloat4(&floatsC, vc);
    float c = floatsC.x;

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
            return {t2, t2};
        }
    }
}

} // namespace zrt