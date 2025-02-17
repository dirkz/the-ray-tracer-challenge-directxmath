#pragma once

#include "stdafx.h"

namespace zrt
{

struct Ray
{
    Ray(FXMVECTOR origin, FXMVECTOR direction);

    inline XMVECTOR Origin() const
    {
        return XMLoadFloat4(&m_origin);
    }

    inline XMVECTOR Direction() const
    {
        return XMLoadFloat4(&m_direction);
    }

  private:
    XMFLOAT4 m_origin;
    XMFLOAT4 m_direction;
};

} // namespace zrt
