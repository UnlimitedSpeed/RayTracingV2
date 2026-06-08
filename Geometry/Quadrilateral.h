#ifndef QUADRILATERAL_HPP
#define QUADRILATERAL_HPP

#include "Object.h"
#include "Triangle.h"
#include <vector>

namespace Geometry
{
    class Quadrilateral : public Object
    {
    private:
        std::vector<Vec3> points;
        std::vector<Triangle> triangles;

    public:
        Quadrilateral(std::vector<Vec3> points, Colour colour) : Object(colour), points(points)
        {
            triangles.push_back(Triangle({points[0], points[1], points[2]}));
            triangles.push_back(Triangle({points[0], points[2], points[3]}));
        }

        bool Hit(Ray r, HitData& hitData) override
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
    };
}

#endif