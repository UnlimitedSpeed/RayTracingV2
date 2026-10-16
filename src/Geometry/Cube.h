#ifndef CUBE_HPP
#define CUBE_HPP

#include "Object.h"

namespace Geometry
{
    class Cube : public Object
    {
    public:
        Cube(Vec3 position, double size, Material* material) : Object(material)
        {
            std::vector<Vec3> vertices;
            const double t = size / 2;
            vertices.push_back({position.x() - t, position.y() - t, position.z() + t});
            vertices.push_back({position.x() + t, position.y() - t, position.z() + t});
            vertices.push_back({position.x() + t, position.y() + t, position.z() + t});
            vertices.push_back({position.x() - t, position.y() + t, position.z() + t});
            vertices.push_back({position.x() - t, position.y() - t, position.z() - t});
            vertices.push_back({position.x() + t, position.y() - t, position.z() - t});
            vertices.push_back({position.x() + t, position.y() + t, position.z() - t});
            vertices.push_back({position.x() - t, position.y() + t, position.z() - t});

            triangles.push_back(Triangle(vertices[0], vertices[1], vertices[2]));
            triangles.push_back(Triangle(vertices[0], vertices[2], vertices[3]));
            triangles.push_back(Triangle(vertices[4], vertices[0], vertices[3]));
            triangles.push_back(Triangle(vertices[4], vertices[3], vertices[7]));
            triangles.push_back(Triangle(vertices[3], vertices[2], vertices[6]));
            triangles.push_back(Triangle(vertices[3], vertices[6], vertices[7]));
            triangles.push_back(Triangle(vertices[1], vertices[5], vertices[6]));
            triangles.push_back(Triangle(vertices[1], vertices[6], vertices[2]));
            triangles.push_back(Triangle(vertices[0], vertices[4], vertices[5]));
            triangles.push_back(Triangle(vertices[0], vertices[5], vertices[1]));
            triangles.push_back(Triangle(vertices[5], vertices[4], vertices[7]));
            triangles.push_back(Triangle(vertices[5], vertices[7], vertices[6]));
        }
    };
}

#endif