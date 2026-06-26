#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include "Geometry/Triangle.h"
#include "helper/Vec3.h"
#include "helper/Ray.h"
#include "helper/HitData.h"
#include "Material/Material.h"

namespace Geometry
{
    class Object
    {
    protected:
        Material *material;
        std::vector<Triangle> triangles;

    public:
        explicit Object(Material *material);
        virtual ~Object();
        virtual bool Hit(Ray r, HitData &hitData, std::vector<double> interval);
    };
}

#endif
