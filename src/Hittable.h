#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"
#include "Vec3.h"
#include "AABB.h"

class Material;

struct HitRecord
{
    Point3 p;
    Vec3 normal;
    std::shared_ptr<Material> matPtr;
    bool frontFace;
    double t;

    inline void setFaceNormal(const Ray& r, const Vec3& outwardNormal)
    {
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
public:
    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const = 0;
    virtual bool boundingBox(double t0, double t1,  AABB& outputBox) const = 0;
};

#endif