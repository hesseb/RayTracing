#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "Ray.h"
#include "Core.h"

class Camera
{
public:
    Camera(Point3 lookFrom, Point3 lookAt, Vec3 viewUp, double vFOV,
           double aspectRatio, double aperture, double focusDist, double t0 = 0, double t1 = 0);

    Ray getRay(double s, double t) const;

private:
    Point3 m_Origin;
    Point3 m_LowerLeftCorner;
    Vec3 m_Horizontal;
    Vec3 m_Vertical;
    Vec3  m_U, m_V, m_W;
    double m_LensRadius;
    double m_Time0, m_Time1;
};

#endif