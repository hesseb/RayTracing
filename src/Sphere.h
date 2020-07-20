#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vec3.h"
#include "Material.h"
#include "AABB.h"

class Sphere: public Hittable
{
public:
    Sphere() = default;
    Sphere(Point3 center, double radius, std::shared_ptr<Material> material)
        : m_Center(center), m_Radius(radius), m_MatPtr(material) {};

    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
    virtual bool boundingBox(double t0, double t1, AABB& outputBox) const override;

    Point3 center() { return m_Center; }
    double radius() { return m_Radius; }
    std::shared_ptr<Material> material() { return m_MatPtr; }

private:
    Point3 m_Center;
    double m_Radius;
    std::shared_ptr<Material> m_MatPtr;
};

#endif