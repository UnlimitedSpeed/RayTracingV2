#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Object.h"
#include "helper/Colour.h"

namespace Geometry
{
    class Triangle : public Object
    {
    private:
        std::vector<Vec3> points;
    public:
        Triangle(std::vector<Vec3> points) : points(points) {}
        Triangle(std::vector<Vec3> points, Colour colour) : Object(colour), points(points) {}
        Vec3 GetNormal() const
        {
            return (points[1] - points[0]).Cross(points[2] - points[0]).UnitVector();
        }

        bool Hit(Ray r, HitData& hitData) override
        {
            const Vec3 e1 = points[1] - points[0];
            const Vec3 e2 = points[2] - points[0];
            const Vec3 P = r.GetDirection().Cross(e2);
            const double determinant = e1.Dot(P);

            if (determinant == 0)
            {
                // No intersection with plane
                return false;
            }

            const Vec3 T = r.GetOrigin() - points[0];
            const double u = T.Dot(P) / determinant;

            if (u > 1 || u < 0)
            {
                return false;
            }

            const Vec3 Q = T.Cross(e1);
            const double v = r.GetDirection().Dot(Q) / determinant;

            if (v < 0 || v + u > 1)
            {
                return false;
            }

            const double t = e2.Dot(Q) / determinant;

            const Vec3 point = r.GetOrigin() + t * r.GetDirection();

            const double distanceFromOrigin = (point - r.GetOrigin()).Length();
            if (distanceFromOrigin <= 0.001 || distanceFromOrigin >= 1000)
            {
                return false;
            }

            hitData.SetNormal(GetNormal());
            hitData.SetPoint(point);

            return true;
        }
    };
}

#endif