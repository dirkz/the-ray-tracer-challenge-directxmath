#include "PerlinNoise.h"

namespace zrt
{

inline float Fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

inline float Lerp(float t, float a, float b)
{
    return a + t * (b - a);
}

PerlinNoise::PerlinNoise()
{
    for (int i = 0; i < GridSize; ++i)
    {
        m_permutations[GridSize + i] = m_permutations[i];
    }
}

float PerlinNoise::Noise(float x, float y, float z)
{
    float fx = std::floor(x);
    float fy = std::floor(y);
    float fz = std::floor(z);

    // The unit cube that contains the point.
    int X = static_cast<int>(fx) & BitMask;
    int Y = static_cast<int>(fy) & BitMask;
    int Z = static_cast<int>(fz) & BitMask;

    // Relative coordinates of the point inside the unit cube.
    x -= fx;
    y -= fy;
    z -= fz;

    return 0.0f;
}

inline int PerlinNoise::Hash(int x, int y, int z)
{
    return m_permutations[m_permutations[m_permutations[x] + y]];
}

inline float PerlinNoise::Grad(int hash, float x, float y, float z)
{
    int h = hash & m_gradients.size() - 1;

    XMVECTOR gridV = XMLoadFloat4(&m_gradients[h]);
    XMVECTOR v = XMVectorSet(x, y, z, 0);

    XMVECTOR dotV = XMVector3Dot(gridV, v);

    return XMVectorGetX(dotV);
}

} // namespace zrt