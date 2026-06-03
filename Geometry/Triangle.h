#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

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

        bool Hit(Ray r) override
        {
            const Vec3 e1 = p2 - p1;
            const Vec3 e2 = p3 - p1;
            const Vec3 P = r.GetDirection().Cross(e2);
            const double determinant = e1.Dot(P);

            if (determinant == 0)
            {
                // No intersection with plane
                return false;
            }


            const Vec3 T = r.GetOrigin() - p1;
            const double u = T.Dot(P) / determinant;

            if (u > 1 || u < 0)
            {
                return false;
            }

            const Vec3 Q = T.Cross(e1);
            const double v = r.GetDirection().Dot(Q) / determinant;

            if ( v < 0 || v + u > 1)
            {
                return false;
            }

            const double t = e2.Dot(Q) / determinant;

            const Vec3 point = r.GetOrigin() + t * r.GetDirection();

            return true;
        }
    };
}

#endif