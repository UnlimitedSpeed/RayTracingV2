#ifndef HITDATA_HPP
#define HITDATA_HPP

#include "helper/Vec3.h"
#include "Material/Material.h"

class HitData
{
private:
    Vec3 point;
    Vec3 normal;
    Material* material;
    double t;

public:
    void SetPoint(Vec3 point) { this->point = point; }
    void SetNormal(Vec3 normal) { this->normal = normal; }
    void SetMaterial(Material* material) { this->material = material; }
    void SetT(double t) { this->t = t; }

    Vec3 GetPoint() { return point; }
    Vec3 GetNormal() { return normal; }
    Material* GetMaterial() { return material; }
    double GetT() { return t; }
};

#endif