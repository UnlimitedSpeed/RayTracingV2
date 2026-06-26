#include <cstdlib>
#include <random>

const double PI = 3.14159265359;

inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max)
{
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

inline double toRadians(double degree)
{
    return (degree * PI) / 180;
}