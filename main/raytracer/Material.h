#pragma once

#include "stdafx.h"

#include "PointLight.h"
#include "Vector.h"

namespace zrt
{

struct Material
{
    Material(FXMVECTOR color = zrt::Color(1, 1, 1), float ambient = 0.1, float diffuse = 0.9,
             float specular = 0.9, float shininess = 200);

    XMVECTOR XM_CALLCONV Lighting(const PointLight &light, FXMVECTOR position, FXMVECTOR eyev,
                                  FXMVECTOR normal) const;

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

} // namespace zrt
