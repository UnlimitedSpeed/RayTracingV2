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
        bool isHit = false;
        for (auto t : triangles)
        {
            isHit |= t.Hit(r, hitData, interval);
            if (isHit)
            {
                hitData.SetMaterial(material);
                return true;
            }
        }
        return isHit;
    }
}
