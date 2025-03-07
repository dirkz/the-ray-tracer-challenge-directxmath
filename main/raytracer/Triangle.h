#pragma once

#include "stdafx.h"

#include "Material.h"
#include "Shape.h"
#include "Vector.h"

namespace zrt
{

struct Triangle : public Shape
{
    Triangle(FXMVECTOR p1, FXMVECTOR p2, FXMVECTOR p3, CXMMATRIX transform = XMMatrixIdentity(),
             const zrt::Material &material = zrt::Material{});

    std::vector<Intersection> LocalIntersect(const Ray &ray) const override;
    XMVECTOR XM_CALLCONV LocalNormal(FXMVECTOR p) const override;

    inline XMVECTOR XM_CALLCONV P1() const
    {
        return XMLoadFloat4(&m_p1);
    }

    inline XMVECTOR XM_CALLCONV P2() const
    {
        return XMLoadFloat4(&m_p2);
    }

    inline XMVECTOR XM_CALLCONV P3() const
    {
        return XMLoadFloat4(&m_p3);
    }

    inline XMVECTOR XM_CALLCONV E1() const
    {
        return XMLoadFloat4(&m_e1);
    }

    inline XMVECTOR XM_CALLCONV E2() const
    {
        return XMLoadFloat4(&m_e2);
    }

    inline XMVECTOR XM_CALLCONV Normal() const
    {
        return XMLoadFloat4(&m_normal);
    }

  private:
    XMFLOAT4 m_p1;
    XMFLOAT4 m_p2;
    XMFLOAT4 m_p3;

    XMFLOAT4 m_e1;
    XMFLOAT4 m_e2;

    XMFLOAT4 m_normal;
};

} // namespace zrt
