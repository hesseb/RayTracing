#include "Vec3.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Core.h"
#include "Material.h"
#include "MovingSphere.h"

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

HittableList randomScene()
{
    HittableList world;

    std::shared_ptr<Material> materialGround = std::make_shared<Lambertian>(Color(0.4, 0.4, 0.4));
    world.add(std::make_shared<Sphere>(Point3( 0, -1000, 0), 1000, materialGround));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            double chooseMat = randomDouble();
            Point3 center(a + 0.9*randomDouble(), 0.2, b+0.9*randomDouble());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9)
            {
                std::shared_ptr<Material> sphereMaterial;

                if (chooseMat < 0.4)
                {
                    //Moving diffuse
                    Color albedo = Color::random() * Color::random();
                    sphereMaterial = std::make_shared<Lambertian>(albedo);
                    Point3 center2 = center + Vec3(0, randomDouble(0, 0.5), 0);
                    world.add(std::make_shared<MovingSphere>(center, center2, 0.0, 1.0, 0.2, sphereMaterial)); 
                }
                else if (chooseMat < 0.8)
                {
                    //Diffuse
                    Color albedo = Color::random() * Color::random();
                    sphereMaterial = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
                else if (chooseMat < 0.95)
                {
                    //Metal
                    Color albedo = Color::random(0.5, 1);
                    double fuzz = randomDouble(0, 0.5);
                    sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
                else
                {
                    //Glass
                    sphereMaterial = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }

    std::shared_ptr<Material> materialGlass = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, materialGlass));

    std::shared_ptr<Material> materialDiffuse = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.2));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, materialDiffuse));

    std::shared_ptr<Material> materialMetal = std::make_shared<Metal>(Color(0.5, 0.6, 0.7), 0.0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, materialMetal));

    return world;
}



int main()
{
    //Image

    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxDepth = 50;

    //World

    HittableList world = randomScene();

   /*
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
*/

    //Camera

    Point3 lookFrom = Point3(13, 2, 3);
    Point3 lookAt = Point3(0, 0, 0);
    Vec3 viewUp = Vec3(0, 1, 0);

    double distToFocus = 10.0; //(lookFrom - lookAt).length();
    double aperture = 0.1;

    Camera camera(lookFrom, lookAt, viewUp, 20.0, aspectRatio, aperture, distToFocus, 0.0, 1.0);

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