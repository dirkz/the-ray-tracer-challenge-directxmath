#pragma once

#include "stdafx.h"

#include "PointLight.h"

class Intersectable;

namespace zrt
{

struct World
{
    World();

    inline const PointLight *Light() const
    {
        return m_light.get();
    }

    inline const std::vector<Intersectable *> &Objects() const
    {
        return m_objects;
    }

  private:
    std::unique_ptr<PointLight> m_light;
    std::vector<Intersectable *> m_objects;
};

} // namespace zrt
