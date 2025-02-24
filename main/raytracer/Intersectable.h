#pragma once

#include "Intersection.h"
#include "Material.h"
#include "Ray.h"

namespace zrt
{

struct Intersectable
{
    Intersectable();
    Intersectable(CXMMATRIX transform, const Material &material = zrt::Material{});

    // Can't copy
    Intersectable(const Intersectable &other) = delete;

    // Can't copy
    void operator=(const Intersectable &other) = delete;

    virtual std::vector<Intersection> Intersect(const Ray &ray) const = 0;

    /// <summary>
    /// The normal vector at the given point, assumed to be part of the object's surface.
    /// </summary>
    /// <param name="p"></param>
    /// <returns></returns>
    virtual XMVECTOR XM_CALLCONV Normal(FXMVECTOR p) const = 0;

    void XM_CALLCONV Transform(CXMMATRIX transform);

    inline XMMATRIX XM_CALLCONV Transform() const
    {
        return XMLoadFloat4x4(&m_transform);
    }

    inline const zrt::Material &Material() const
    {
        return m_material;
    }

  protected:
    inline XMMATRIX XM_CALLCONV InverseTransform() const
    {
        return XMLoadFloat4x4(&m_inverseTransform);
    }

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
bool operator==(const Intersectable &i1, const Intersectable &i2);

} // namespace zrt
