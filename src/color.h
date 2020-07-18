#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include "Core.h"

#include <iostream>

void writeColor(std::ostream &out, Color pixelColor, int samplesPerPixel)
{
    double r = pixelColor.x();
    double g = pixelColor.y();
    double b = pixelColor.z();

    double scale = 1.0 / samplesPerPixel;
    r = std::sqrt(scale * r);
    g = std::sqrt(scale * g);
    b = std::sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif