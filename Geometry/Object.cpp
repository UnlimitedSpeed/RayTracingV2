#include "Object.h"
#include "Triangle.h"

namespace Geometry
{
    Object::Object()
    {
        this->material = new Material();
    }

    Object::Object(Material* material)
    {
        this->material = material;
    }
    Object::~Object() = default;

    bool Object::Hit(Ray r, HitData &hitData, std::vector<double> interval)
    {
        double closestT = interval[1];


        bool isHit = false;
        for (auto t : triangles)
        {
            isHit |= t.Hit(r, hitData, {interval[0], closestT});
            if (isHit)
            {
                hitData.SetMaterial(material);
                closestT = hitData.GetT();
            }
        }
        return isHit;
    }
}
