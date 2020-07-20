#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "Hittable.h"
#include "Vec3.h"
#include "Ray.h"
#include "Core.h"
#include "AABB.h"

class MovingSphere : public Hittable
{
public:
    MovingSphere() = default;
    MovingSphere(Point3 center0, Point3 center1, double t0, double t1, double radius, std::shared_ptr<Material> material)
        : m_Center0(center0), m_Center1(center1), m_Time0(t0), m_Time1(t1), m_Radius(radius), m_MatPtr(material) {}

    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& record) const override;
    virtual bool boundingBox(double t0, double t1, AABB& outputBox) const override;

    Point3 center(double time) const;
    
private:
    Point3 m_Center0, m_Center1;
    double m_Time0, m_Time1;
    double m_Radius;
    std::shared_ptr<Material> m_MatPtr;
};

#endif