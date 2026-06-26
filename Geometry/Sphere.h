#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Object.h"
#include "math.h"
#include "helper/Utils.h"

namespace Geometry
{
    class Sphere : public Object
    {
    public:
        Sphere(Vec3 position, double radius, int sides, int height, Material *material) : Object(material)
        {
            std::vector<std::vector<Vec3>> vertices;
            const double sideAngle = 360.0 / sides;
            const double heightAngle = 180.0 / height;

            for (double i = 0; i < 360; i += sideAngle)
            {
                std::vector<Vec3> vert;
                for (double j = 0; j < 180.0; j += heightAngle)
                {
                    const double iRadians = toRadians(i);
                    const double jRadians = toRadians(j);
                    const Vec3 unitCoordinate = {sin(jRadians) * cos(iRadians), cos(jRadians), sin(jRadians) * sin(iRadians)};
                    const Vec3 coordinate = unitCoordinate * radius + position;
                    vert.push_back(coordinate);
                }
                vertices.push_back(vert);
            }

            for (size_t i = 0; i < vertices.size() - 1; i++)
            {
                const std::vector<Vec3> &vert1 = vertices[i];
                const std::vector<Vec3> &vert2 = vertices[i + 1];
                for (size_t j = 0; j < vert1.size() - 1; j++)
                {
                    triangles.push_back(Triangle(vert1[j], vert2[j + 1], vert2[j]));
                    triangles.push_back(Triangle(vert1[j], vert1[j + 1], vert2[j + 1]));
                }
            }
        }
    };
}

#endif