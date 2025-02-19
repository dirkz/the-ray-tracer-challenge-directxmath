#pragma once

#include "stdafx.h"

namespace zrt
{

struct Material
{
    Material(FXMVECTOR color, float ambient, float diffuse, float specular, float shininess);

    inline XMVECTOR XM_CALLCONV Color() const
    {
        return XMLoadFloat4(&m_color);
    }

    inline float Ambient() const
    {
        return m_ambient;
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
