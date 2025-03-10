#pragma once

#include "Intersection.h"
#include "Material.h"
#include "Ray.h"

namespace zrt
{

struct Group;

struct Shape
{
    Shape(CXMMATRIX transform = XMMatrixIdentity(), const Material &material = zrt::Material{});

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

    XMVECTOR XM_CALLCONV WorldToObjectPoint(FXMVECTOR worldPoint) const;
    XMVECTOR XM_CALLCONV ObjectToWorldNormal(FXMVECTOR objectNormal) const;

    void Parent(Group *group);

    inline Group *Parent() const
    {
        return m_parent;
    }

    inline bool HasParent() const
    {
        return m_parent != nullptr;
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
    Group *m_parent;

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
