#pragma once

#include "stdafx.h"

#include "Shape.h"

namespace zrt
{

struct Cylinder : public Shape
{
    Cylinder(CXMMATRIX transform = XMMatrixIdentity(),
             const zrt::Material &material = zrt::Material{},
             float minimum = -std::numeric_limits<float>::infinity(),
             float maximum = std::numeric_limits<float>::infinity());

    std::vector<Intersection> LocalIntersect(const Ray &ray) const override;
    XMVECTOR XM_CALLCONV LocalNormal(FXMVECTOR p) const override;

  private:
    float m_minimum;
    float m_maximum;
};

} // namespace zrt
