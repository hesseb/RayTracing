#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vec3.h"

class Sphere: public Hittable
{
public:
    Sphere() = default;
    Sphere(Point3 center, double radius)
        : m_Center(center), m_Radius(radius) {};

    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;

    Point3 center() { return m_Center; }
    double radius() { return m_Radius; }

private:
    Point3 m_Center;
    double m_Radius;
};

#endif