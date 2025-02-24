#include "PerlinNoise.h"

namespace zrt
{

static inline float Fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

static inline float Lerp(float t, float a, float b)
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

float PerlinNoise::Noise(float x, float y, float z) const
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

    // Fade curves.
    float u = Fade(x);
    float v = Fade(y);
    float w = Fade(z);

    // Hash coordinates of the 8 cube corners.
    int A = m_permutations[X] + Y, AA = m_permutations[A] + Z, AB = m_permutations[A + 1] + Z,
        B = m_permutations[X + 1] + Y, BA = m_permutations[B] + Z, BB = m_permutations[B + 1] + Z;

    float result = Lerp(
        w,
        Lerp(v, Lerp(u, Grad(m_permutations[AA], x, y, z), Grad(m_permutations[BA], x - 1, y, z)),
             Lerp(u, Grad(m_permutations[AB], x, y - 1, z),
                  Grad(m_permutations[BB], x - 1, y - 1, z))),
        Lerp(v,
             Lerp(u, Grad(m_permutations[AA + 1], x, y, z - 1),
                  Grad(m_permutations[BA + 1], x - 1, y, z - 1)),
             Lerp(u, Grad(m_permutations[AB + 1], x, y - 1, z - 1),
                  Grad(m_permutations[BB + 1], x - 1, y - 1, z - 1))));

    return result;
}

inline float PerlinNoise::Grad(int hash, float x, float y, float z) const
{
    int h = hash & m_gradients.size() - 1;

    XMVECTOR gridV = XMLoadFloat4(&m_gradients[h]);
    XMVECTOR v = XMVectorSet(x, y, z, 0);

    XMVECTOR dotV = XMVector3Dot(gridV, v);

    return XMVectorGetX(dotV);
}

} // namespace zrt