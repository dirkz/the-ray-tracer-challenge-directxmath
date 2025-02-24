#pragma once

#include "stdafx.h"

#include "Intersectable.h"
#include "Material.h"

namespace zrt
{

struct Pattern
{
    Pattern(CXMMATRIX transform)
    {
        XMStoreFloat4x4(&m_transform, transform);
        XMStoreFloat4x4(&m_inverseTransform, XMMatrixInverse(nullptr, transform));
    };

    XMVECTOR WorldToObjectPosition(const Intersectable *object, FXMVECTOR position) const
    {
        XMMATRIX m = object->InverseTransform();
        return XMVector4Transform(position, m);
    }

    XMVECTOR ObjectToPatternPosition(FXMVECTOR objectPosition) const
    {
        return XMVector4Transform(objectPosition, InverseTransform());
    }

    XMVECTOR PatternPosition(const Intersectable *object, FXMVECTOR position) const
    {
        XMVECTOR objectPosition = WorldToObjectPosition(object, position);
        return ObjectToPatternPosition(objectPosition);
    }

    XMMATRIX Transform() const
    {
        return XMLoadFloat4x4(&m_transform);
    }

    XMMATRIX InverseTransform() const
    {
        return XMLoadFloat4x4(&m_inverseTransform);
    }

  private:
    XMFLOAT4X4 m_transform;
    XMFLOAT4X4 m_inverseTransform;
};

struct StripePattern : public Pattern
{
    StripePattern(FXMVECTOR color, FXMMATRIX transform = XMMatrixIdentity()) : Pattern{transform}
    {
        XMStoreFloat4(&m_color, color);
    }

    XMVECTOR XM_CALLCONV operator()(const Intersectable *object, FXMVECTOR position,
                                    FXMVECTOR color) const
    {
        XMVECTOR patternPosition = PatternPosition(object, position);

        float x = XMVectorGetX(patternPosition);
        float m = std::fmod(x, 2.f);
        float fm = std::floor(m);
        if (std::abs(fm) == 1.f)
        {
            return XMLoadFloat4(&m_color);
        }
        else
        {
            return color;
        }
    }

  private:
    XMFLOAT4 m_color;
};

struct CirclePattern : public Pattern
{
    CirclePattern(FXMVECTOR color, FXMMATRIX transform = XMMatrixIdentity()) : Pattern{transform}
    {
        XMStoreFloat4(&m_color, color);
    }

    XMVECTOR XM_CALLCONV operator()(const Intersectable *object, FXMVECTOR position,
                                    FXMVECTOR color) const
    {
        XMVECTOR patternPosition = PatternPosition(object, position);

        XMFLOAT4 floats;
        XMStoreFloat4(&floats, patternPosition);

        XMVECTOR v = XMVectorSet(floats.x, 0.f, floats.z, 0.f);
        XMVECTOR dv = XMVector3Length(v);

        float distance = XMVectorGetX(dv);
        float m = std::fmod(distance, 2.f);
        float fm = std::floor(m);
        if (std::abs(fm) == 1.f)
        {
            return XMLoadFloat4(&m_color);
        }
        else
        {
            return color;
        }
    }

  private:
    XMFLOAT4 m_color;
};

} // namespace zrt
