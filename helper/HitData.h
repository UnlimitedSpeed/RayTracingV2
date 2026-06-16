#ifndef HITDATA_HPP
#define HITDATA_HPP

#include "helper/Vec3.h"
#include "helper/Colour.h"

class HitData
{
private:
    Vec3 point;
    Vec3 normal;
    Colour colour;
    double t;

public:
    void SetPoint(Vec3 point) { this->point = point; }
    void SetNormal(Vec3 normal) { this->normal = normal; }
    void SetColour(Colour colour) { this->colour = colour; }
    void SetT(double t) { this->t = t; }

    Vec3 GetPoint() { return point; }
    Vec3 GetNormal() { return normal; }
    Colour GetColour() { return colour; }
    double GetT() { return t; }
};

#endif