#include "HittableList.h"

bool HittableList::hit(const Ray& r, double tMin, double tMax, HitRecord& record) const
{
    HitRecord tempRecord;
    bool hitAnything = false;
    double closestSoFar = tMax;

    for (const auto& object : objects)
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