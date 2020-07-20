#include "Material.h"


bool Lambertian::scatter(const Ray& rIn, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    Vec3 scatterDirection = record.normal + randomUnitVector();
    scattered = Ray(record.p, scatterDirection, rIn.time());
    attenuation = m_Albedo;
    return true;
}

bool Metal::scatter(const Ray& rIn, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    Vec3 reflected = reflect(unitVector(rIn.direction()), record.normal);
    scattered = Ray(record.p, reflected + m_Fuzz * randomInUnitSphere(), rIn.time());
    attenuation = m_Albedo;
    return (dot(scattered.direction(), record.normal) > 0);
}

bool Dielectric::scatter(const Ray& rIn, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    attenuation = Color(1.0, 1.0, 1.0);
    double etaFraction = record.frontFace ? 1.0 / m_RefIdx : m_RefIdx;

    Vec3 unitDirection = unitVector(rIn.direction());
    
    double cosTheta = fmin(dot(-unitDirection, record.normal), 1.0);
    double sinTheta = std::sqrt(1.0 - cosTheta*cosTheta);

    if (etaFraction * sinTheta > 1.0) 
    {
        Vec3 reflected = reflect(unitDirection, record.normal);
        scattered = Ray(record.p, reflected, rIn.time());
        return true;
    }

    double reflectProb = schlick(cosTheta, etaFraction);
    if (randomDouble() < reflectProb)
    {
        Vec3 reflected = reflect(unitDirection, record.normal);
        scattered = Ray(record.p, reflected, rIn.time());
        return true;
    }

    Vec3 refracted = refract(unitDirection,  record.normal, etaFraction);
    scattered = Ray(record.p, refracted, rIn.time());
    return true;
}

double schlick(double cosine, double refIdx)
{
    double r0 = (1-refIdx) / (1+refIdx);
    r0 = r0*r0;
    return r0 + (1-r0) * pow((1 - cosine), 5);
}