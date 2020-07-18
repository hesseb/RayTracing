#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Core.h"

#include <iostream>

Color rayColor(const Ray& r, const Hittable& world, int depth)
{
    HitRecord record;

    if (depth <= 0)
        return Color(0.0, 0.0, 0.0);

    if (world.hit(r, 0.001, g_Infinity, record))
    {
        Point3 target = record.p + record.normal + randomInUnitSphere();
        return 0.5 * rayColor(Ray(record.p, target - record.p), world, depth - 1);
    }
    Vec3 unitDirection = unitVector(r.direction());
    double t = 0.5*(unitDirection.y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

int main()
{
    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 640;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxDepth = 50;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    Camera camera;

    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

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