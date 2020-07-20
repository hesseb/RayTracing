#ifndef CORE_H
#define CORE_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>


constexpr double g_Infinity = std::numeric_limits<double>::infinity();
constexpr double g_Pi = 3.14159265358979323846;

inline double radians(double degrees)
{
    return degrees * g_Pi / 180;
}

inline double randomDouble()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double randomDouble(double min, double max)
{
    return min + randomDouble() * (max - min);
}

inline int randomInt(int min, int max)
{
    return static_cast<int>(randomDouble(min, max+1));
}

inline double clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#endif