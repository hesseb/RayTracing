#include "Vec3.h"

Vec3 randomInUnitSphere()
{
    while (true)
    {
        Vec3 p = Vec3::random(-1, 1);
        if (p.lengthSquared() < 1) return p;
    }
}

Vec3 randomUnitVector()
{
    double phi = randomDouble(0, 2*g_Pi);
    double z = randomDouble(-1, 1);
    double r = std::sqrt(1- z*z);
    return Vec3(r*cos(phi), r*sin(phi), z);
}

Vec3 randomInUnitDisc()
{
    while (true)
    {
        Point3 p = Vec3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if (p.lengthSquared() < 1) return p;
    }
}

Vec3 randomInHemisphere(const Vec3& normal)
{
    Vec3 inUnitSphere = randomInUnitSphere();
    if (dot(inUnitSphere, normal) > 0.0) //same hemisphere as normal
        return inUnitSphere;
    else
        return -inUnitSphere;
}

Vec3 reflect(const Vec3& v, const Vec3& normal)
{
    return v - 2*dot(v, normal)*normal;
}

Vec3 refract(const Vec3& uv, const Vec3& normal, double etaFraction)
{
    double cosTheta = dot(-uv, normal);
    Vec3 rOutParallel = etaFraction * (uv + cosTheta*normal);
    Vec3 rOutPerpendicular = -std::sqrt(fabs(1.0 - rOutParallel.lengthSquared())) * normal;
    return rOutParallel + rOutPerpendicular;
}