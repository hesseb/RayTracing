#include "Vec3.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Core.h"
#include "Material.h"

#include <iostream>

Color rayColor(const Ray& r, const Hittable& world, int depth)
{
    HitRecord record;

    if (depth <= 0)
        return Color(0.0, 0.0, 0.0);

    if (world.hit(r, 0.001, g_Infinity, record))
    {
        Ray scattered;
        Color attenuation;
        if (record.matPtr->scatter(r, record, attenuation, scattered))
        {
            return attenuation * rayColor(scattered, world, depth - 1);
        }
        return Color(0.0, 0.0, 0.0);
    }
    Vec3 unitDirection = unitVector(r.direction());
    double t = 0.5*(unitDirection.y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

int main()
{
    //Image

    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 640;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxDepth = 50;

    //World

    HittableList world;

    std::shared_ptr<Material> materialGround = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    std::shared_ptr<Material> materialBlueDiffuse = std::make_shared<Lambertian>(Color(0.2, 0.3, 0.8));
    std::shared_ptr<Material> materialMetal = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);
    std::shared_ptr<Material> materialGlass = std::make_shared<Dielectric>(1.5);

    world.add(std::make_shared<Sphere>(Point3( 0,      0, -1),   0.5, materialBlueDiffuse));
    world.add(std::make_shared<Sphere>(Point3( 0, -100.5, -1), 100.0, materialGround));
    
    world.add(std::make_shared<Sphere>(Point3( 1,      0, -1),   0.5, materialMetal));
    world.add(std::make_shared<Sphere>(Point3(-1,      0, -1),   0.5, materialGlass));
    world.add(std::make_shared<Sphere>(Point3(-1,      0, -1), -0.45, materialGlass));

    //Camera

    Point3 lookFrom = Point3(3, 3, 2);
    Point3 lookAt = Point3(0, 0, -1);
    Vec3 viewUp = Vec3(0, 1, 0);

    double distToFocus = (lookFrom - lookAt).length();
    double aperture = 0.0;

    Camera camera(lookFrom, lookAt, viewUp, 20.0, aspectRatio, aperture, distToFocus);

    //Render

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight-1; j>= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i)
        {
            Color pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s)
            {
                double u = (i + randomDouble()) / (imageWidth-1);
                double v = (j + randomDouble()) / (imageHeight-1);
                Ray r = camera.getRay(u, v);
                pixelColor += rayColor(r, world, maxDepth);
            }
            writeColor(std::cout, pixelColor, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
}