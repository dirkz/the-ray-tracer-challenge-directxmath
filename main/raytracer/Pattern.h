#pragma once

#include "stdafx.h"

#include "Intersectable.h"
#include "Material.h"
#include "PerlinNoise.h"

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

struct NoisePattern : public Pattern
{
    NoisePattern(FXMMATRIX transform = XMMatrixIdentity()) : Pattern{transform}
    {
    }

    XMVECTOR XM_CALLCONV operator()(const Intersectable *object, FXMVECTOR position,
                                    FXMVECTOR color) const
    {
        XMVECTOR patternPosition = PatternPosition(object, position);

        XMFLOAT4 floats;
        XMStoreFloat4(&floats, patternPosition);

        float noise = m_noise.Noise(floats.x, floats.y, floats.z);
        float scaledNoise = noise / 2.f + 1.f;

        XMVECTOR scaledColor = XMVectorScale(color, scaledNoise);
        XMVECTOR clampedColor = XMVectorClamp(scaledColor, XMVectorZero(), XMVectorSplatOne());

        return clampedColor;
    }

  private:
    PerlinNoise m_noise;
};

template <class A, class B> struct AddPattern
{
    AddPattern(A &pattern1, B &pattern2) : m_pattern1{pattern1}, m_pattern2{pattern2}
    {
    }

    XMVECTOR XM_CALLCONV operator()(const Intersectable *object, FXMVECTOR position,
                                    FXMVECTOR color) const
    {
        XMVECTOR c1 = m_pattern1(object, position, color);
        XMVECTOR c2 = m_pattern2(object, position, color);
        XMVECTOR sum = XMVectorAdd(c1, c2);
        XMVECTOR clamped = XMVectorClamp(sum, XMVectorZero(), XMVectorSplatOne());
        return clamped;
    }

  private:
    A &m_pattern1;
    B &m_pattern2;
};

} // namespace zrt
