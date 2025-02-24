#pragma once

#include "PointLight.h"
#include "Vector.h"

namespace zrt
{

struct Material
{
    Material(FXMVECTOR color = zrt::Color(1, 1, 1), float ambient = 0.1, float diffuse = 0.9,
             float specular = 0.9, float shininess = 200);

    virtual XMVECTOR XM_CALLCONV Lighting(const PointLight &light, FXMVECTOR position,
                                          FXMVECTOR eyev, FXMVECTOR normal,
                                          bool isInLight = true) const;

    inline XMVECTOR XM_CALLCONV Color() const
    {
        return XMLoadFloat4(&m_color);
    }

    inline float Ambient() const
    {
        return m_ambient;
    }

    inline void Ambient(float f)
    {
        m_ambient = f;
    }

    inline float Diffuse() const
    {
        return m_diffuse;
    }

    inline float Specular() const
    {
        return m_specular;
    }

    inline float Shininess() const
    {
        return m_shininess;
    }

  private:
    XMFLOAT4 m_color;
    float m_ambient;
    float m_diffuse;
    float m_specular;
    float m_shininess;
};

struct NoPattern
{
    XMVECTOR XM_CALLCONV operator()(FXMVECTOR position, FXMVECTOR color) const
    {
        return color;
    }
};

template <class T>
XMVECTOR XM_CALLCONV Lighting(const Material &material, const PointLight &light, FXMVECTOR position,
                              FXMVECTOR eyev, FXMVECTOR normal, bool isInLight,
                              const T &pattern = NoPattern)
{
    XMVECTOR diffuse = XMVectorZero();
    XMVECTOR specular = XMVectorZero();

    XMVECTOR color = pattern(position, material.Color());

    XMVECTOR effectiveColor = XMColorModulate(color, light.Intensity());
    XMVECTOR lightv = XMVector4Normalize(XMVectorSubtract(light.Position(), position));
    XMVECTOR ambient = XMVectorScale(effectiveColor, material.Ambient());

    float lightDotNormal = XMVectorGetX(XMVector4Dot(lightv, normal));
    if (lightDotNormal < 0)
    {
        diffuse = zrt::Color(0, 0, 0);
    }
    else
    {
        diffuse = XMVectorScale(XMVectorScale(effectiveColor, material.Diffuse()), lightDotNormal);
        XMVECTOR reflectv = Reflect(XMVectorScale(lightv, -1), normal);
        float reflectDotEye = XMVectorGetX(XMVector4Dot(reflectv, eyev));
        if (reflectDotEye <= 0)
        {
            specular = zrt::Color(0, 0, 0);
        }
        else
        {
            float factor = std::pow(reflectDotEye, material.Shininess());
            specular = XMVectorScale(XMVectorScale(light.Intensity(), material.Specular()), factor);
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

struct StripePattern
{
    StripePattern(XMVECTOR color)
    {
        XMStoreFloat4(&m_color, color);
    }

    XMVECTOR XM_CALLCONV operator()(FXMVECTOR position, FXMVECTOR color) const
    {
        float x = XMVectorGetX(position);
        float m = std::fmod(std::abs(x), 2.f);
        float fm = std::floor(m);
        if (fm == 1.f)
        {
            return XMLoadFloat4(&m_color);
        }
        else
        {
            return color;
        }
    }

  private:
    XMFLOAT4 m_color;
};

template <class T> struct PatternedMaterial : public Material
{
    PatternedMaterial(const T &pattern, FXMVECTOR color = zrt::Color(1, 1, 1), float ambient = 0.1,
                      float diffuse = 0.9, float specular = 0.9, float shininess = 200)
        : Material{color, ambient, diffuse, specular, shininess}, m_pattern{pattern}
    {
    }

    XMVECTOR XM_CALLCONV Lighting(const PointLight &light, FXMVECTOR position, FXMVECTOR eyev,
                                  FXMVECTOR normal, bool isInLight = true) const override
    {
        return zrt::Lighting(*this, light, position, eyev, normal, isInLight, m_pattern);
    }

  private:
    const T &m_pattern;
};

} // namespace zrt
