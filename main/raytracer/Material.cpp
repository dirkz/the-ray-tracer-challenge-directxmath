#include "Material.h"

namespace zrt
{

Material::Material(FXMVECTOR color, float ambient, float diffuse, float specular, float shininess)
    : m_ambient{ambient}, m_diffuse{diffuse}, m_specular{specular}, m_shininess{shininess}
{
    XMStoreFloat4(&m_color, color);
}

XMVECTOR XM_CALLCONV Material::Lighting(const PointLight &light, FXMVECTOR position, FXMVECTOR eyev,
                                        FXMVECTOR normal)
{
    return Vector(0, 0, 0);
}

} // namespace zrt