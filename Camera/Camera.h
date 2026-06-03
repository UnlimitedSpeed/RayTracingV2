#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "helper/Vec3.h"
#include "helper/Ray.h"
#include "helper/Colour.h"

class Camera
{
private:
    double aspectRatio;
    int imageWidth;
    int imageHeight;
    double focalLength;
    double viewportHeight;
    double viewportWidth;
    Vec3 position;
    Vec3 viewportU;
    Vec3 viewportV;
    Vec3 pixelDeltaU;
    Vec3 pixelDeltaV;
    Vec3 viewportUpperLeft;
    Vec3 pixel0Location;

public:
    Camera(double aspectRatio, int imageWidth, double focalLength, double viewportHeight);
    ~Camera() {};

    Colour RayColour(const Ray& ray);
    Ray GetRay(int h, int w);
    void Render();
};

#endif