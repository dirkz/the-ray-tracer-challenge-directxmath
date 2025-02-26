#pragma once

namespace zrt
{

struct Shape;

struct Intersection
{
    Intersection(const Shape *pShape, float t);

    inline const Shape *Object() const
    {
        return m_pShape;
    }

    inline float T() const
    {
        return m_t;
    }

    inline Intersection &operator=(const Intersection &other)
    {
        m_pShape = other.m_pShape;
        m_t = other.m_t;

        return *this;
    }

  private:
    const Shape *m_pShape;
    float m_t;
};

std::ostream &operator<<(std::ostream &os, const Intersection &i);

bool operator==(const Intersection &s1, const Intersection &s2);

struct IntersectionLess
{
    bool operator()(const Intersection &s1, const Intersection &s2) const;
};

std::vector<Intersection> Intersections(std::initializer_list<Intersection> intersections);

/// <summary>
/// The first intersection with a distance > 0 from an order list of intersections.
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
const Intersection *Hit(const std::vector<Intersection> &list);

} // namespace zrt
