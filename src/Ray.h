#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray
{
public:
    Ray() = default;
    Ray(const Point3& origin, const Vec3& direction, double time = 0.0)
        : m_Origin(origin), m_Direction(direction), m_Time(time) {}

    Point3 origin() const { return m_Origin; }
    Vec3 direction() const { return m_Direction; }
    double time() const { return m_Time; }

    Point3 at(double t) const
    {
        return m_Origin + t*m_Direction;
    }

private:
    Point3 m_Origin;
    Vec3 m_Direction;
    double m_Time;
};

#endif