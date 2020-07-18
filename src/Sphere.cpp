#include "Sphere.h"

bool Sphere::hit(const Ray& r, double tMin, double tMax, HitRecord& record) const
{
    Vec3 oc = r.origin() - m_Center;
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
            Vec3 outwardNormal = (record.p - m_Center) / m_Radius;
            record.setFaceNormal(r, outwardNormal);
            record.matPtr = m_MatPtr;
            return true;
        }
        temp = (-halfB + root) / a;
        if (temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.p = r.at(record.t);
            Vec3 outwardNormal = (record.p - m_Center) / m_Radius;
            record.setFaceNormal(r, outwardNormal);
            record.matPtr = m_MatPtr;
            return true;
        }
    }

    return false;
}