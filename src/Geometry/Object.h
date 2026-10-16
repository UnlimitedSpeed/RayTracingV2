#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include "src/Geometry/Triangle.h"
#include "src/helper/Vec3.h"
#include "src/helper/Ray.h"
#include "src/helper/HitData.h"
#include "src/Material/Material.h"

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
