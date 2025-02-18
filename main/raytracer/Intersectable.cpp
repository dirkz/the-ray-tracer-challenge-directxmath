#include "Intersectable.h"

namespace zrt
{

Intersectable::Intersectable()
{
}

bool Intersectable::operator==(const Intersectable &other)
{
    return this == &other;
}

} // namespace zrt