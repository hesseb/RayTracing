#include "Camera.h"

//Takes Vertical FOV in degrees
Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 viewUp, double vFOV, double aspectRatio, double aperture, double focusDist)
    : m_Origin(lookFrom), m_LensRadius(aperture / 2)
{
    double theta = radians(vFOV);
    double h = tan(theta/2);
    double viewportHeight = 2.0 * h;
    double viewportWidth = aspectRatio * viewportHeight;
    
    m_W = unitVector(lookFrom - lookAt);
    m_U = unitVector(cross(viewUp, m_W));
    m_V = cross(m_W, m_U);

    m_Horizontal = focusDist * viewportWidth * m_U;
    m_Vertical = focusDist * viewportHeight * m_V;
    m_LowerLeftCorner = m_Origin - m_Horizontal/2 - m_Vertical/2 - focusDist*m_W;
}

Ray Camera::getRay(double s, double t) const
{
    Vec3 rd = m_LensRadius * randomInUnitDisc();
    Vec3 offset = m_U * rd.x() + m_V * rd.y();

    return Ray(m_Origin + offset, m_LowerLeftCorner + s*m_Horizontal + t*m_Vertical - m_Origin - offset);
}