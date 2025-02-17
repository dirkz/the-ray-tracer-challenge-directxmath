#include "Sphere.h"

namespace zrt
{

std::vector<float> Sphere::Intersect(const Ray &ray)
{
    // The sphere is at the origin
    XMVECTOR sphereToRay = ray.Origin();

    XMVECTOR va = XMVector4Dot(ray.Direction(), ray.Direction());
    XMVECTOR vb = XMVectorScale(XMVector4Dot(ray.Direction(), sphereToRay), 2);
    XMVECTOR vc = XMVectorSubtract(XMVector4Dot(sphereToRay, sphereToRay), XMVectorReplicate(1));

    XMVECTOR vDiscriminant =
        XMVectorSubtract(XMVectorMultiply(vb, vb), XMVectorScale(XMVectorMultiply(va, vc), 2));

    XMFLOAT4 floatsD;
    XMStoreFloat4(&floatsD, vDiscriminant);

    float discriminant = floatsD.x;

    if (discriminant < 0)
    {
        return {};
    }
    else
    {
        XMFLOAT4 floatsA, floatsB;
        XMStoreFloat4(&floatsA, va);
        XMStoreFloat4(&floatsB, vb);

        float a = floatsA.x;
        float b = floatsB.x;

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