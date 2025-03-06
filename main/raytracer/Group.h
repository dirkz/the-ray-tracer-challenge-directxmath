#pragma once

#include "stdafx.h"

#include "Shape.h"

namespace zrt
{

struct Group : public Shape
{
    using Shape::Shape;

    std::vector<Intersection> LocalIntersect(const Ray &ray) const override;
    XMVECTOR XM_CALLCONV LocalNormal(FXMVECTOR p) const override;

    bool Empty() const;
};

} // namespace zrt
