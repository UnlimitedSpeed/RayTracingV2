#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Triangle.h"
#include "math.h"
#include "helper/Utils.h"

namespace Geometry
{
    class Sphere : public Object
    {
    private:
    public:
        Sphere(Vec3 position, double radius, int sides, int height, Material *material) : Object(material)
        {
            std::vector<std::vector<Vec3>> vertices;
            const double sideAngle = 360.0 / sides;
            const double heightAngle = 180.0 / height;
            std::clog << "Create Sphere:\n" << std::flush;
            
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

            for (int i = 0; i < vertices.size() - 1; i++)
            {
                std::vector<Vec3> vert1 = vertices[i];
                std::vector<Vec3> vert2 = vertices[i+1];
                for (int j = 0; j < vert1.size() - 1; j++)
                {
                    Triangle t1 = Triangle({vert1[j], vert2[j+1], vert2[j]});
                    triangles.push_back(t1);
                    Triangle t2 = Triangle({vert1[j], vert1[j+1], vert2[j+1]});
                    triangles.push_back(t2);
                }
                
            }
            


        }
    };
}

#endif