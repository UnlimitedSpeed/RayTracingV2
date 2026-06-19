#include "helper/Colour.h"

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

class Material
{
private:
    Colour colour;
    float metallic;
    float roughness;
    float ior;
    float transmission;
public:
    Material() : colour(Colour()), metallic(0), roughness(1), ior(0), transmission(0) {};
    Material(Colour colour, float metallic, float roughness, float ior, float transmission) : 
        colour(colour), metallic(metallic), roughness(roughness), ior(ior), transmission(transmission) {};
    Colour GetColour() { return colour; }
    float GetMetallic() { return metallic; }
    float GetRoughness() { return roughness; }
    float GetIOR() { return ior; }
    float GetTransmission() { return transmission; }
};


#endif