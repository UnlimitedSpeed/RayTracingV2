#ifndef RAY_HPP
#define RAY_HPP

#include "Vec3.h"

class Ray
{
    private:
        Vec3 origin;
        Vec3 direction;
    public:
        Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction) {};
        ~Ray();
        const Vec3 At(double t) { return origin + direction * t; };
        const Vec3& GetOrigin() { return origin; };
        const Vec3& GetDirection() { return direction; };
};

#endif