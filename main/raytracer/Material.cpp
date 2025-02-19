#include "Material.h"

namespace zrt
{

Material::Material(FXMVECTOR color, float ambient, float diffuse, float specular, float shininess)
    : m_ambient{ambient}, m_diffuse{diffuse}, m_specular{specular}, m_shininess{shininess}
{
    XMStoreFloat4(&m_color, color);
}

} // namespace zrt