#pragma once

#include "Ray.h"
#include "Shape.h"

namespace zrt
{

struct Computations
{
    Computations(const Intersection &i, const Ray &r, std::vector<Intersection> intersections);

    inline const Shape *Object() const
    {
        return m_pShape;
    }

    inline XMVECTOR XM_CALLCONV Point() const
    {
        return XMLoadFloat4(&m_point);
    }

    inline XMVECTOR XM_CALLCONV OverPoint() const
    {
        return XMLoadFloat4(&m_overPoint);
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

    inline XMVECTOR XM_CALLCONV ReflectV() const
    {
        return XMLoadFloat4(&m_reflectv);
    }

  private:
    float m_t;
    const Shape *m_pShape;
    bool m_inside;

    XMFLOAT4 m_point;
    XMFLOAT4 m_overPoint;
    XMFLOAT4 m_eyev;
    XMFLOAT4 m_normal;
    XMFLOAT4 m_reflectv;
};

} // namespace zrt
