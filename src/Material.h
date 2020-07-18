#ifndef MATERIAL_H
#define MATERIAL_H


#include "Ray.h"
#include "Vec3.h"
#include "Hittable.h"

class Material
{
public:
    virtual bool scatter( const Ray& rIn, const HitRecord& record, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const Color& albedo)
        : m_Albedo(albedo) {}

    virtual bool scatter(const Ray& rIn, const HitRecord& record, Color& attenuation, Ray& scattered) const override;

    inline Color albedo() { return m_Albedo; }

private:
    Color m_Albedo;
};

class Metal : public Material
{
public:
    Metal(const Color& albedo, double fuzz)
        : m_Albedo(albedo), m_Fuzz(fuzz < 1 ? fuzz : 1) {}

    virtual bool scatter(const Ray& rIn, const HitRecord& record, Color& attenuation, Ray& scattered) const override;

    inline Color albedo() { return m_Albedo; }

private:
    Color m_Albedo;
    double m_Fuzz;
};

class Dielectric : public Material
{
public:
    Dielectric(double refIdx)
        : m_RefIdx(refIdx) {}
    
    virtual bool scatter(const Ray& rIn, const HitRecord& record, Color& attenuation, Ray& scattered) const override;

    inline double refIdx() { return m_RefIdx; }

private:
    double m_RefIdx;
};

double schlick(double cosine, double refIdx);

#endif