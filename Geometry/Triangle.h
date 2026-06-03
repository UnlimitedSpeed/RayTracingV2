#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "helper/Vec3.h"
#include "Object.h"

namespace Geometry
{
    class Triangle : public Object
    {
        private:
            Vec3 p1;
            Vec3 p2;
            Vec3 p3;

        public:
            Triangle(Vec3 p1, Vec3 p2, Vec3 p3) : p1(p1), p2(p2), p3(p3) {}
            Vec3 GetNormal() const 
            {
                return (p2 - p1).Cross(p3 - p1).UnitVector();
            }
    };
}

#endif