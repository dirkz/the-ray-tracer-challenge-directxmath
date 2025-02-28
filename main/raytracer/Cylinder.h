#pragma once

#include "stdafx.h"

#include "Shape.h"

namespace zrt
{

struct Cylinder : public Shape
{
    using Shape::Shape;

    std::vector<Intersection> LocalIntersect(const Ray &ray) const override;
    XMVECTOR XM_CALLCONV Normal(FXMVECTOR p) const override;
};

} // namespace zrt
