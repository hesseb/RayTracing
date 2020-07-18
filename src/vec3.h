#ifndef VEC3_H
#define VEC3_H

#include "Core.h"
#include <cmath>
#include <iostream>

class Vec3
{
public:
    Vec3()
        : m_E{0,0,0} {}
    Vec3(double e0, double e1, double e2)
        : m_E{e0, e1, e2} {}

    double x() const { return m_E[0]; }
    double y() const { return m_E[1]; }
    double z() const { return m_E[2]; }

    Vec3 operator-() const { return Vec3(-m_E[0], -m_E[1], -m_E[2]); }
    double operator[](int i) const { return m_E[i]; }
    double& operator[](int i) { return m_E[i]; }
    
    Vec3& operator+=(const Vec3 &v)
    {
        m_E[0] += v.m_E[0];
        m_E[1] += v.m_E[1];
        m_E[2] += v.m_E[2];
        return *this;
    }

    Vec3& operator*=(const double t)
    {
        m_E[0] *= t;
        m_E[1] *= t;
        m_E[2] *= t;
        return *this;
    }

    Vec3& operator/=(const double t)
    {
        return *this *= 1/t;
    }

    double length() const
    {
        return std::sqrt(lengthSquared());
    }

    double lengthSquared() const
    {
        return m_E[0]*m_E[0] + m_E[1]*m_E[1] + m_E[2]*m_E[2];
    }

    inline static Vec3 random()
    {
        return Vec3(randomDouble(), randomDouble(), randomDouble());
    }

    inline static Vec3 random(double min, double max)
    {
        return Vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
    }


public:
    double m_E[3];
};

using Point3 = Vec3;
using Color = Vec3;

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v)
{
    return out << v.m_E[0] << ' ' << v.m_E[1] << ' ' << v.m_E[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.m_E[0] + v.m_E[0], u.m_E[1] + v.m_E[1], u.m_E[2] + v.m_E[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.m_E[0] - v.m_E[0], u.m_E[1] - v.m_E[1], u.m_E[2] - v.m_E[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.m_E[0] * v.m_E[0], u.m_E[1] * v.m_E[1], u.m_E[2] * v.m_E[2]);
}

inline Vec3 operator*(double t, const Vec3 &v)
{
    return Vec3(t * v.m_E[0], t * v.m_E[1], t * v.m_E[2]);
}

inline Vec3 operator*(const Vec3 &v, double t)
{
    return t * v;
}

inline Vec3 operator/(const Vec3 &v, double t)
{
    return (1/t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v)
{
    return u.m_E[0] * v.m_E[0] + u.m_E[1] * v.m_E[1] + u.m_E[2] * v.m_E[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.m_E[1] * v.m_E[2] - u.m_E[2] * v.m_E[1],
                u.m_E[2] * v.m_E[0] - u.m_E[0] * v.m_E[2],
                u.m_E[0] * v.m_E[1] - u.m_E[1] * v.m_E[0]);
}

inline Vec3 unitVector(Vec3 v)
{
    return v / v.length();
}

Vec3 randomInUnitSphere();

Vec3 randomUnitVector();

Vec3 randomInUnitDisc();

Vec3 randomInHemisphere(const Vec3& normal);


Vec3 reflect(const Vec3& v, const Vec3& normal);

Vec3 refract(const Vec3& uv, const Vec3& normal, double etaFraction);


#endif