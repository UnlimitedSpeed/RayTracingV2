#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>
#include <SDL3/SDL.h>
#include "src/helper/Vec3.h"
#include "src/helper/Ray.h"
#include "src/helper/Colour.h"
#include "src/helper/HitData.h"
#include "src/World/World.h"
#include <memory>
#include <atomic>

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
    void DrawBuffer(SDL_Renderer *renderer, const std::vector<Colour> &colourBuffer) const;
    void ThreadColour(
        const std::vector<std::unique_ptr<Geometry::Object>> &objs,
        const std::vector<Vec3> &lights,
        std::vector<Colour> &colourBuffer,
        int lowerBound,
        int upperBound,
        std::atomic<int> &finishedThreads
    );

public:
    Camera(double aspectRatio, int imageWidth, double focalLength, double viewportHeight);
    ~Camera() {};

    bool HitInterval(const Ray &ray, const std::vector<std::unique_ptr<Geometry::Object>> &objs, HitData &hitData);
    Colour RayColour(const Ray &ray, const std::vector<std::unique_ptr<Geometry::Object>> &objs, const std::vector<Vec3> &lights, int depth);
    Ray GetRay(int h, int w);
    void Render(SDL_Renderer *renderer, const World &world, bool &running);
};

#endif