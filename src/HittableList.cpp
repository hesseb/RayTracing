#include "HittableList.h"

bool HittableList::hit(const Ray& r, double tMin, double tMax, HitRecord& record) const
{
    HitRecord tempRecord;
    bool hitAnything = false;
    double closestSoFar = tMax;

    for (const auto& object : m_Objects)
    {
        if (object->hit(r, tMin, closestSoFar, tempRecord))
        {
            hitAnything = true;
            closestSoFar = tempRecord.t;
            record = tempRecord;
        }
    }

    return hitAnything;
}

bool HittableList::boundingBox(double t0, double t1, AABB& outputBox) const
{
    if (m_Objects.empty()) return false;

    AABB tempBox;
    bool firstBox = true;

    for (const auto& object : m_Objects)
    {
        if (!object->boundingBox(t0, t1, tempBox)) return false;
        outputBox = firstBox ? tempBox : surroundingBox(outputBox, tempBox);
        firstBox = false;
    }

    return true;
}