#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>
#include "helper/Vec3.h"
#include "helper/Ray.h"
#include "helper/Colour.h"
#include "Geometry/Object.h"
#include "helper/HitData.h"

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

    const int maxDepth = 5;

public:
    Camera(double aspectRatio, int imageWidth, double focalLength, double viewportHeight);
    ~Camera() {};

    Colour RayColour(const Ray& ray, std::vector<Geometry::Object*> objs, int depth = 0);
    Ray GetRay(int h, int w);
    void Render(std::vector<Geometry::Object*> objs);
};

#endif