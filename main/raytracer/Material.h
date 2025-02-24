#pragma once

#include "PointLight.h"
#include "Vector.h"

namespace zrt
{

struct ConstPattern
{
    inline XMVECTOR XM_CALLCONV operator()(FXMVECTOR p, FXMVECTOR c) const
    {
        return c;
    }
};

template <class T> struct MaterialWithPattern
{
    MaterialWithPattern(FXMVECTOR color = zrt::Color(1, 1, 1), float ambient = 0.1,
                        float diffuse = 0.9, float specular = 0.9, float shininess = 200,
                        T pattern = ConstPattern{})
        : m_ambient{ambient}, m_diffuse{diffuse}, m_specular{specular}, m_shininess{shininess},
          m_pattern{pattern}
    {
        XMStoreFloat4(&m_color, color);
    }

    inline XMVECTOR XM_CALLCONV Lighting(const PointLight &light, FXMVECTOR position,
                                         FXMVECTOR eyev, FXMVECTOR normal,
                                         bool isInLight = true) const
    {
        XMVECTOR diffuse = XMVectorZero();
        XMVECTOR specular = XMVectorZero();

        XMVECTOR effectiveColor = XMColorModulate(m_pattern(position, Color()), light.Intensity());
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
    T m_pattern;
};

using Material = MaterialWithPattern<ConstPattern>;

} // namespace zrt
