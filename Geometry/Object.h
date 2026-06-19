#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include "helper/Vec3.h"
#include "helper/Ray.h"
#include "helper/HitData.h"
#include "Material/Material.h"

namespace Geometry
{
    class Triangle;

    class Object
    {
    private:
        Material* material;
    protected:
        std::vector<Triangle> triangles;
    public:
        Object();
        Object(Material* material);
        virtual ~Object();
        virtual bool Hit(Ray r, HitData &hitData, std::vector<double> interval);
    };
}

#endif