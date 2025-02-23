#include "Material.h"

namespace zrt
{

Material::Material(FXMVECTOR color, float ambient, float diffuse, float specular, float shininess)
    : m_ambient{ambient}, m_diffuse{diffuse}, m_specular{specular}, m_shininess{shininess}
{
    XMStoreFloat4(&m_color, color);
}

XMVECTOR XM_CALLCONV Material::Lighting(const PointLight &light, FXMVECTOR position, FXMVECTOR eyev,
                                        FXMVECTOR normal, bool isInLight) const
{
    XMVECTOR diffuse = XMVectorZero();
    XMVECTOR specular = XMVectorZero();

    XMVECTOR effectiveColor = XMColorModulate(Color(), light.Intensity());
    XMVECTOR lightv = XMVector4Normalize(XMVectorSubtract(light.Position(), position));
    XMVECTOR ambient = XMVectorScale(effectiveColor, Ambient());

    float lightDotNormal = XMVectorGetX(XMVector4Dot(lightv, normal));
    if (lightDotNormal < 0)
    {
        diffuse = zrt::Color(0, 0, 0);
    }
    else
    {
        diffuse = XMVectorScale(XMVectorScale(effectiveColor, Diffuse()), lightDotNormal);
        XMVECTOR reflectv = Reflect(XMVectorScale(lightv, -1), normal);
        float reflectDotEye = XMVectorGetX(XMVector4Dot(reflectv, eyev));
        if (reflectDotEye <= 0)
        {
            specular = zrt::Color(0, 0, 0);
        }
        else
        {
            float factor = std::pow(reflectDotEye, Shininess());
            specular = XMVectorScale(XMVectorScale(light.Intensity(), Specular()), factor);
        }
    }

    XMVECTOR sumv = ambient;

    if (isInLight)
    {
        sumv = XMVectorAdd(sumv, diffuse);
        sumv = XMVectorAdd(sumv, specular);
    }

    sumv = XMVectorSetW(sumv, 1);

    return sumv;
}

} // namespace zrt