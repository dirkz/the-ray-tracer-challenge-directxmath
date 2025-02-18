#include "Intersectable.h"

namespace zrt
{

Intersectable::Intersectable()
{
}

bool operator==(const Intersectable &i1, const Intersectable &i2)
{
    return &i1 == &i2;
}

} // namespace zrt