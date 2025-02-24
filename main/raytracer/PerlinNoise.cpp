#include "PerlinNoise.h"

namespace zrt
{

inline float Smootherstep(float edge0, float edge1, float x)
{
    x = std::clamp((x - edge0) / (edge1 - edge0), 0.f, 1.f);
    return x * x * x * (x * (6.0f * x - 15.0f) + 10.0f);
}

PerlinNoise::PerlinNoise()
{
    for (int i = 0; i < NumGradients; ++i)
    {
        m_permutations[NumGradients + i] = m_permutations[i];
    }
}

float PerlinNoise::Noise(float x, float y, float z)
{
    // The unit cube that contains the point.
    int X = static_cast<int>(std::floor(x)) & BitMask;
    int Y = static_cast<int>(std::floor(y)) & BitMask;
    int Z = static_cast<int>(std::floor(z)) & BitMask;

    return 0.0f;
}

inline int PerlinNoise::Hash(int x, int y, int z)
{
    return m_permutations[m_permutations[m_permutations[x] + y]];
}

} // namespace zrt