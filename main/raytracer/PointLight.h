#pragma once

#include "stdafx.h"

namespace zrt
{

struct PointLight
{
    PointLight(FXMVECTOR position, FXMVECTOR intensity);

    inline XMVECTOR XM_CALLCONV Position() const
    {
        return XMLoadFloat4(&m_position);
    }

    inline XMVECTOR XM_CALLCONV Intensity() const
    {
        return XMLoadFloat4(&m_intensity);
    }

    friend bool operator==(const PointLight &, const PointLight &);

  private:
    XMFLOAT4 m_position;
    XMFLOAT4 m_intensity;
};

inline bool operator==(const PointLight &l1, const PointLight &l2)
{
    XMFLOAT4 fp1 = l1.m_position;
    XMFLOAT4 fp2 = l2.m_position;
    XMFLOAT4 fi1 = l1.m_intensity;
    XMFLOAT4 fi2 = l2.m_intensity;

    return fp1.x == fp2.x && fp1.y == fp2.y && fp1.z == fp2.z && fp1.w == fp2.w && fi1.x == fi2.x &&
           fi1.y == fi2.y && fi1.z == fi2.z && fi1.w == fi2.w;
}

} // namespace zrt
