#ifndef AABB_H
#define AABB_H

#include "Core.h"
#include "Vec3.h"
#include "Ray.h"


class AABB
{
public:
    AABB() = default;
    AABB(const Point3& a, const Point3& b)
        : m_Min(a), m_Max(b) {}

    Point3 min() { return m_Min; }
    Point3 max() { return m_Max; }

    bool hit(const Ray& r, double tMin, double tMax) const;

private:
    Point3 m_Min;
    Point3 m_Max;
};

AABB surroundingBox(AABB box0, AABB box1);

#endif