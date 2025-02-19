#include "PointLight.h"

namespace zrt
{

PointLight::PointLight(FXMVECTOR position, FXMVECTOR intensity)
{
    XMStoreFloat4(&m_position, position);
    XMStoreFloat4(&m_intensity, intensity);
}

XMVECTOR XM_CALLCONV PointLight::Position()
{
    return XMLoadFloat4(&m_position);
}

XMVECTOR XM_CALLCONV PointLight::Intensity()
{
    return XMLoadFloat4(&m_intensity);
}

} // namespace zrt