#include "AABB.h"

bool AABB::hit(const Ray& r, double tMin, double tMax) const
{
    for (int i = 0; i < 3; i++)
    {
        double inverseDirection = 1.0 / r.direction()[i];
        double t0 = (m_Min[i] - r.origin()[i]) * inverseDirection;
        double t1 = (m_Max[i] - r.origin()[i]) * inverseDirection;

        if (inverseDirection < 0.0f) std::swap(t0, t1);

        tMin = t0 > tMin ? t0 : tMin;
        tMax = t1 < tMax ? t1 : tMax;

        if (tMax <= tMin) return false;
    }
    return true;
}

AABB surroundingBox(AABB box0, AABB box1)
{
    Point3 small(fmin(box0.min().x(), box1.min().x()),
                 fmin(box0.min().y(), box1.min().y()),
                 fmin(box0.min().z(), box1.min().z()));
    Point3 big(fmax(box0.max().x(), box1.max().x()),
               fmax(box0.max().y(), box1.max().y()),
               fmax(box0.max().z(), box1.max().z()));

    return AABB(small, big);
}