#ifndef TRIANGLE_OBJECT_HPP
#define TRIANGLE_OBJECT_HPP

#include "Object.h"

namespace Geometry
{
    class TriangleObject : public Object
    {
    public:
        TriangleObject(const Triangle &triangle, Material *material) : Object(material)
        {
            triangles.push_back(triangle);
        }
    };
}

#endif
