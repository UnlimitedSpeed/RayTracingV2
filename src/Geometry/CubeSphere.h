#ifndef CUBICSPHERE_HPP
#define CUBICSPHERE_HPP

#include "Object.h"

#include <array>
#include <cmath>
#include <stdexcept>

namespace Geometry
{
    class CubeSphere : public Object
    {
    public:
        CubeSphere(Vec3 position, double radius, int subdivisions, Material* material) : Object(material)
        {
            // Create the vertices of the cube
            std::array<Vec3, 8> CubeVertices = {
                Vec3(-1, -1, -1),
                Vec3(1, -1, -1),
                Vec3(1, 1, -1), //
                Vec3(-1, 1, -1), //
                Vec3(-1, -1, 1),
                Vec3(1, -1, 1),
                Vec3(1, 1, 1), //
                Vec3(-1, 1, 1) //
            };

            // Create the faces of the cube using the vertices
            std::array<std::array<int, 4>, 6> CubeFaces = {{
                {0, 1, 2, 3}, // Back face
                {4, 5, 6, 7}, // Front face
                {0, 1, 5, 4}, // Bottom face
                {2, 3, 7, 6}, // Top face
                {0, 3, 7, 4}, // Left face
                {1, 2, 6, 5}  // Right face
            }};

            const double step = 2.0 / subdivisions;

            for (const auto& face : CubeFaces)
            {
                Vec3 direction0to1 = CubeVertices[face[1]] - CubeVertices[face[0]];
                Vec3 direction0to3 = CubeVertices[face[3]] - CubeVertices[face[0]];

                for (int i = 0; i < subdivisions; i++)
                {
                    for (int j = 0; j < subdivisions; j++)
                    {
                        Vec3 v0 = CubeVertices[face[0]] + direction0to1 * (i * step) + direction0to3 * (j * step);
                        Vec3 v1 = CubeVertices[face[0]] + direction0to1 * ((i + 1) * step) + direction0to3 * (j * step);
                        Vec3 v2 = CubeVertices[face[0]] + direction0to1 * ((i + 1) * step) + direction0to3 * ((j + 1) * step);
                        Vec3 v3 = CubeVertices[face[0]] + direction0to1 * (i * step) + direction0to3 * ((j + 1) * step);

                        // Project the vertices onto the sphere
                        v0 = v0.UnitVector() * radius + position;
                        v1 = v1.UnitVector() * radius + position;
                        v2 = v2.UnitVector() * radius + position;
                        v3 = v3.UnitVector() * radius + position;

                        // Create two triangles for each square face
                        triangles.push_back(Triangle(v0, v1, v2));
                        triangles.push_back(Triangle(v0, v2, v3));
                    }
                }
            }
        }
    };
}

#endif