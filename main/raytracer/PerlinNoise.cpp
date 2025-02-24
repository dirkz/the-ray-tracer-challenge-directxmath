#include "PerlinNoise.h"

namespace zrt
{

PerlinNoise::PerlinNoise()
{
    for (int i = 0; i < NumGradients; ++i)
    {
        m_permutations[NumGradients + i] = m_permutations[i];
    }
}

inline int PerlinNoise::Hash(int x, int y, int z)
{
    return m_permutations[m_permutations[m_permutations[x] + y]];
}

} // namespace zrt