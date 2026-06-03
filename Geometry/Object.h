#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "helper/Vec3.h"
#include "helper/Ray.h"

namespace Geometry
{
    class Object
    {
    protected:
        Vec3 position;

        virtual bool Hit(Ray r) = 0;

    public:
        Object() {}
    };
}

#endif