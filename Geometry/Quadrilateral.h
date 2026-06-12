#ifndef QUADRILATERAL_HPP
#define QUADRILATERAL_HPP

#include "Triangle.h"

namespace Geometry
{
    class Quadrilateral : public Object
    {
    public:
        Quadrilateral(std::vector<Vec3> points, Colour colour) : Object(colour)
        {
            triangles.push_back(Triangle({points[0], points[1], points[2]}));
            triangles.push_back(Triangle({points[0], points[2], points[3]}));
        }
    };
}

#endif