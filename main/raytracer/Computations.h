#pragma once

#include "stdafx.h"

#include "Intersectable.h"
#include "Intersection.h"
#include "Ray.h"

namespace zrt
{

struct Computations
{
    Computations(const Intersection &i, const Ray &r);

    inline const Intersectable *Object() const
    {
        return m_pIntersectable;
    }

    inline XMVECTOR XM_CALLCONV Point() const
    {
        return XMLoadFloat4(&m_point);
    }

    inline XMVECTOR XM_CALLCONV EyeV() const
    {
        return XMLoadFloat4(&m_eyev);
    }

    inline XMVECTOR XM_CALLCONV Normal() const
    {
        return XMLoadFloat4(&m_normal);
    }

    inline bool IsInside() const
    {
        return m_inside;
    }

  private:
    float m_t;
    const Intersectable *m_pIntersectable;
    bool m_inside;

    XMFLOAT4 m_point;
    XMFLOAT4 m_eyev;
    XMFLOAT4 m_normal;
};

} // namespace zrt
