#pragma once

#include "stdafx.h"

namespace zrt
{

struct Ray
{
    Ray(FXMVECTOR origin, FXMVECTOR direction);

    inline XMVECTOR XM_CALLCONV Origin() const
    {
        return XMLoadFloat4(&m_origin);
    }

    inline XMVECTOR XM_CALLCONV Direction() const
    {
        return XMLoadFloat4(&m_direction);
    }

    inline XMVECTOR XM_CALLCONV Position(float t) const
    {
        XMVECTOR direction = XMVectorScale(Direction(), t);
        return XMVectorAdd(Origin(), direction);
    }

    inline Ray XM_CALLCONV Transform(FXMMATRIX m)
    {
        XMVECTOR origin = XMVector4Transform(Origin(), m);
        XMVECTOR direction = XMVector4Transform(Direction(), m);
        return Ray{origin, direction};
    }

  private:
    XMFLOAT4 m_origin;
    XMFLOAT4 m_direction;
};

} // namespace zrt
