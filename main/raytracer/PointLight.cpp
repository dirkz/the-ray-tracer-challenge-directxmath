#include "PointLight.h"

namespace zrt
{

PointLight::PointLight(FXMVECTOR position, FXMVECTOR intensity)
{
    XMStoreFloat4(&m_position, position);
    XMStoreFloat4(&m_intensity, intensity);
}

} // namespace zrt