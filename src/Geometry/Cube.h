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

            std::array<std::array<int, 6>, 6> faceIndices = {{
                {0, 1, 2, 0, 2, 3}, // Back face
                {4, 5, 6, 4, 6, 7}, // Front face
                {0, 4, 7, 0, 7, 3}, // Left face
                {1, 5, 6, 1, 6, 2}, // Right face
                {3, 2, 6, 3, 6, 7}, // Top face
                {0, 1, 5, 0, 5, 4}  // Bottom face
            }};

            for (const auto& indices : faceIndices)
            {
                triangles.push_back(Triangle(vertices[indices[0]], vertices[indices[1]], vertices[indices[2]]));
                triangles.push_back(Triangle(vertices[indices[3]], vertices[indices[4]], vertices[indices[5]]));
            }
        }
    };
}

#endif