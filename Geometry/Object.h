#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "helper/Vec3.h"
#include "helper/Ray.h"
#include "helper/HitData.h"

namespace Geometry
{
    class Object
    {
    protected:
        Colour colour;

    public:
        Object() {}
        Object(Colour colour) : colour(colour) {}
        virtual bool Hit(Ray r, HitData& hitData) = 0;
        Colour GetColour() { return colour; }
    };
}

#endif