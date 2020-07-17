#include "Color.h"
#include "Core.h"
#include "HittableList.h"
#include "Sphere.h"

#include <iostream>

Color rayColor(const Ray& r, const Hittable& world)
{
    HitRecord record;
    if (world.hit(r, 0, g_Infinity, record))
    {
        return 0.5 * (record.normal + Color(1, 1, 1));
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

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    double viewportHeight = 2.0;
    double viewportWidth = aspectRatio * viewportHeight;
    double focalLength = 1.0;

    Point3 origin = Point3(0, 0, 0);
    Vec3 horizontal = Vec3(viewportWidth, 0, 0);
    Vec3 vertical = Vec3(0, viewportHeight, 0);
    Vec3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);

    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    for (int j = imageHeight-1; j>= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i)
        {
            double u = (double) i / (imageWidth-1);
            double v = (double) j / (imageHeight-1);
            Ray r(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
            Color pixelColor = rayColor(r, world);
            writeColor(std::cout, pixelColor);
        }
    }

    std::cerr << "\nDone.\n";
}