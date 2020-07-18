#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "Ray.h"
#include "Core.h"

class Camera
{
public:
    Camera();

    Ray getRay(double u, double v) const
    {
        return Ray(m_Origin, m_LowerLeftCorner + u*m_Horizontal + v*m_Vertical - m_Origin);
    }

private:
    Point3 m_Origin;
    Point3 m_LowerLeftCorner;
    Vec3 m_Horizontal;
    Vec3 m_Vertical;
};

#endif