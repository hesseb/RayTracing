#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

#include "Ray.h"
#include "Vec3.h"

constexpr double g_Infinity = std::numeric_limits<double>::infinity();
constexpr double g_Pi = 3.14159265358979323846;

inline double radians(double degrees)
{
    return degrees * g_Pi / 180;
}

