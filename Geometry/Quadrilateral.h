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
        Vec3 p1;
        Vec3 p2;
        Vec3 p3;
        Vec3 p4;
        std::vector<Triangle> triangles;

    public:
        Quadrilateral(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4) : p1(p1), p2(p2), p3(p3), p4(p4)
        {
            triangles.push_back(Triangle(p1, p2, p3));
            triangles.push_back(Triangle(p1, p3, p4));
        }

        bool Hit(Ray r) override
        {
            bool isHit = false;
            for (auto t : triangles)
            {
                isHit |= t.Hit(r);
            }
            return isHit;
        }
    };
}

#endif