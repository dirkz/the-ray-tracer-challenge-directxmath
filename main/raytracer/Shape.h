#pragma once

#include "Intersection.h"
#include "Material.h"
#include "Ray.h"

namespace zrt
{

struct Shape
{
    Shape();
    Shape(CXMMATRIX transform, const Material &material = zrt::Material{});

    // Can't copy
    Shape(const Shape &other) = delete;

    // Can't copy
    void operator=(const Shape &other) = delete;

    std::vector<Intersection> Intersect(const Ray &ray) const;

    XMVECTOR XM_CALLCONV Normal(FXMVECTOR worldPoint) const;

    virtual std::vector<Intersection> LocalIntersect(const Ray &ray) const = 0;

    virtual XMVECTOR XM_CALLCONV LocalNormal(FXMVECTOR worldPoint) const = 0;

    void XM_CALLCONV Transform(CXMMATRIX transform);

    inline XMMATRIX XM_CALLCONV Transform() const
    {
        return XMLoadFloat4x4(&m_transform);
    }

    inline XMMATRIX XM_CALLCONV InverseTransform() const
    {
        return XMLoadFloat4x4(&m_inverseTransform);
    }

    inline const zrt::Material &Material() const
    {
        return m_material;
    }

    inline XMVECTOR XM_CALLCONV ObjectPoint(FXMVECTOR worldPoint) const
    {
        return XMVector4Transform(worldPoint, InverseTransform());
    }

    inline XMVECTOR XM_CALLCONV WorldNormal(FXMVECTOR objectNormal) const
    {
        XMVECTOR worldNormal = XMVector4Transform(objectNormal, TransposedInverseTransform());
        worldNormal = XMVectorSetW(worldNormal, 0);
        return XMVector3Normalize(worldNormal);
    }

  protected:
    inline XMMATRIX XM_CALLCONV TransposedInverseTransform() const
    {
        return XMLoadFloat4x4(&m_transposedInverseTransform);
    }

  private:
    XMFLOAT4X4 m_transform;
    XMFLOAT4X4 m_inverseTransform;
    XMFLOAT4X4 m_transposedInverseTransform;
    const zrt::Material &m_material;

    void CreateDerivedTransforms(CXMMATRIX transform);
};

/// <summary>
/// Equality by identity (simple pointer comparison).
/// </summary>
/// <param name="i1"></param>
/// <param name="i2"></param>
/// <returns></returns>
bool operator==(const Shape &i1, const Shape &i2);

} // namespace zrt
