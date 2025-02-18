#pragma once

#include "stdafx.h"

#include "Intersection.h"
#include "Ray.h"

namespace zrt
{

struct Intersectable
{
    Intersectable();
    Intersectable(CXMMATRIX transform);

    // Can't copy
    Intersectable(const Intersectable &other) = delete;

    // Can't copy
    void operator=(const Intersectable &other) = delete;

    virtual std::vector<Intersection> Intersect(const Ray &ray) = 0;

    void XM_CALLCONV Transform(CXMMATRIX transform);
    XMMATRIX XM_CALLCONV Transform();

  private:
    XMFLOAT4X4 m_transform;
};

/// <summary>
/// Equality by identity (simple pointer comparison).
/// </summary>
/// <param name="i1"></param>
/// <param name="i2"></param>
/// <returns></returns>
bool operator==(const Intersectable &i1, const Intersectable &i2);

} // namespace zrt
