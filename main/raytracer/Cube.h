#pragma once

#include "Shape.h"

namespace zrt
{

struct Cube : public Shape
{
    using Shape::Shape;

    std::vector<Intersection> LocalIntersect(const Ray &ray) const override;
    XMVECTOR XM_CALLCONV LocalNormal(FXMVECTOR p) const override;
};

} // namespace zrt
