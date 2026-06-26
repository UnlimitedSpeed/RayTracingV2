#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <vector>

#include "helper/Ray.h"
#include "helper/HitData.h"
#include "helper/Vec3.h"

namespace Geometry
{
    struct Triangle
    {
        Vec3 v0;
        Vec3 v1;
        Vec3 v2;

        Triangle(Vec3 v0, Vec3 v1, Vec3 v2) : v0(v0), v1(v1), v2(v2) {}

        Vec3 GetNormal() const
        {
            return (v1 - v0).Cross(v2 - v0).UnitVector();
        }

        bool Hit(Ray r, HitData &hitData, const std::vector<double> &interval) const
        {
            const Vec3 e1 = v1 - v0;
            const Vec3 e2 = v2 - v0;
            const Vec3 P = r.GetDirection().Cross(e2);
            const double determinant = e1.Dot(P);

            if (determinant == 0)
            {
                return false;
            }

            const Vec3 T = r.GetOrigin() - v0;
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

            Vec3 direction = r.GetDirection();
            const double distanceAlongRay = t * direction.Length();

            if (distanceAlongRay <= interval[0] || distanceAlongRay >= interval[1])
            {
                return false;
            }

            const Vec3 point = r.GetOrigin() + t * direction;

            hitData.SetNormal(GetNormal());
            hitData.SetPoint(point);
            hitData.SetT(distanceAlongRay);

            return true;
        }
    };
}

#endif