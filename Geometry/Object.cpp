#include "Object.h"
#include "Triangle.h"

namespace Geometry
{
    Object::Object()
    {
        this->colour = Colour();
    }

    Object::Object(Colour colour)
    {
        this->colour = colour;
    }
    Object::~Object() = default;

    bool Object::Hit(Ray r, HitData& hitData)
    {
        bool isHit = false;
        for (auto t : triangles)
        {
            isHit |= t.Hit(r, hitData);
            if (isHit)
            {
                hitData.SetColour(colour);
                return true;
            }
        }
        return isHit;
    }
}
