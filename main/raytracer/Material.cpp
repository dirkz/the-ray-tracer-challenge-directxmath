#include "Material.h"

namespace zrt
{

Material::Material(FXMVECTOR color, float ambient, float diffuse, float specular, float shininess,
                   float reflective, float transparency, float refractiveIndex)
    : m_ambient{ambient}, m_diffuse{diffuse}, m_specular{specular}, m_shininess{shininess},
      m_reflective{reflective}, m_transparency{transparency}, m_refractiveIndex{refractiveIndex}
{
    XMStoreFloat4(&m_color, color);
}

XMVECTOR XM_CALLCONV Material::Lighting(const Shape *object, const PointLight &light,
                                        FXMVECTOR position, FXMVECTOR eyev, FXMVECTOR normal,
                                        bool isInLight) const
{
    return zrt::Lighting(*this, object, light, position, eyev, normal, isInLight, NoPattern{});
}

} // namespace zrt