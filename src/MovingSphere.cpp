#include "MovingSphere.h"

bool MovingSphere::hit(const Ray& r, double tMin, double tMax, HitRecord& record) const
{
    Vec3 oc = r.origin() - center(r.time());
    double a = r.direction().lengthSquared();
    double halfB = dot(oc, r.direction());
    double c = oc.lengthSquared() - m_Radius*m_Radius;
    double discriminant = halfB*halfB - a*c;
    
    if (discriminant > 0)
    {
        double root = std::sqrt(discriminant);
        double temp = (-halfB - root)/a;
        if (temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.p = r.at(record.t);
            Vec3 outwardNormal = (record.p - center(r.time())) / m_Radius;
            record.setFaceNormal(r, outwardNormal);
            record.matPtr = m_MatPtr;
            return true;
        }

        temp = (-halfB + root) / a;
        if (temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.p = r.at(record.t);
            Vec3 outwardNormal = (record.p - center(r.time())) / m_Radius;
            record.setFaceNormal(r, outwardNormal);
            record.matPtr = m_MatPtr;
            return true;
        }
    }

    return false;
}

Point3 MovingSphere::center(double time) const
{
    return m_Center0 + ((time - m_Time0) / (m_Time1 - m_Time0)) * (m_Center1 - m_Center0);
}

bool MovingSphere::boundingBox(double t0, double t1, AABB& outputBox) const
{
    AABB box0(
        center(t0) - Vec3(m_Radius, m_Radius, m_Radius),
        center(t0) + Vec3(m_Radius, m_Radius, m_Radius));
    AABB box1(
        center(t1) - Vec3(m_Radius, m_Radius, m_Radius),
        center(t1) + Vec3(m_Radius, m_Radius, m_Radius));
    
    outputBox = surroundingBox(box0, box1);
    
    return true;
}