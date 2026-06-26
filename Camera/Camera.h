#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>
#include <SDL2/SDL.h>
#include "helper/Vec3.h"
#include "helper/Ray.h"
#include "helper/Colour.h"
#include "helper/HitData.h"
#include <memory>

namespace Geometry
{
    class Object;
}

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
    const int samples_per_pixel = 4;
    const double MAX_INTERVAL = INFINITY;

    Vec3 SampleSquare();
public:
    Camera(double aspectRatio, int imageWidth, double focalLength, double viewportHeight);
    ~Camera() {};

    bool HitInterval(const Ray &ray, const std::vector<std::unique_ptr<Geometry::Object>>& objs, HitData &hitData);
    Colour RayColour(const Ray &ray, const std::vector<std::unique_ptr<Geometry::Object>>& objs, const std::vector<Vec3>& lights, int depth = 0);
    Ray GetRay(int h, int w);
    void Render(SDL_Renderer* renderer, const std::vector<std::unique_ptr<Geometry::Object>>& objs, const std::vector<Vec3>& lights, bool& running);
};

#endif