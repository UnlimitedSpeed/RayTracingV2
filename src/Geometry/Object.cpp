#include "Object.h"

namespace Geometry
{
    Object::Object(Material *material) : material(material) {}

    Object::~Object() = default;

    bool Object::Hit(Ray r, HitData &hitData, std::vector<double> interval)
    {
        double closestT = interval[1];
        bool isHit = false;
        for (const auto &tri : triangles)
        {
            if (tri.Hit(r, hitData, {interval[0], closestT}))
            {
                isHit = true;
                hitData.SetMaterial(material);
                closestT = hitData.GetT();
            }
        }
        return isHit;
    }
}
