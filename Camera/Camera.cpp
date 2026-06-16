#include <iostream>

#include "Camera.h"
#include "Geometry/Object.h"

Camera::Camera(double aspectRatio, int imageWidth, double focalLength, double viewportHeight)
{
    this->aspectRatio = aspectRatio;
    this->imageWidth = imageWidth;
    this->imageHeight = int(imageWidth / aspectRatio);

    this->focalLength = focalLength;
    this->viewportHeight = viewportHeight;
    this->viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    this->position = Vec3();

    this->viewportU = Vec3(viewportWidth, 0, 0);
    this->viewportV = Vec3(0, -viewportHeight, 0);

    this->pixelDeltaU = viewportU / imageWidth;
    this->pixelDeltaV = viewportV / imageHeight;

    this->viewportUpperLeft = position - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
    this->pixel0Location = viewportUpperLeft + pixelDeltaU / 2 + pixelDeltaV / 2;
}

bool Camera::HitInterval(const Ray &ray, std::vector<Geometry::Object*> objs, HitData &hitData)
{
    HitData hitTemp;

    bool isHit = false;

    const double minT = 0.001;
    double closestT = MAX_INTERVAL;

    for (auto obj : objs)
    {
        std::clog << "Between " << minT << " and " << closestT << std::endl << std::flush;
        if (obj->Hit(ray, hitTemp, {minT, closestT}))
        {
            isHit = true;
            closestT = hitTemp.GetT();
            hitData = hitTemp;
        }
    }
    if (isHit)
        std::clog << "isHit: " << isHit << "\n" << std::flush; 
    return isHit;
}

Colour Camera::RayColour(const Ray &ray, std::vector<Geometry::Object *> objs, int depth)
{
    if (depth > maxDepth)
    {
        return Colour();
    }

    HitData hitData;
    if (HitInterval(ray, objs, hitData))
    {
        Vec3 newDirection = ray.GetDirection() - 2 * ray.GetDirection().Dot(hitData.GetNormal()) * hitData.GetNormal();
        Ray newRay = Ray(hitData.GetPoint(), newDirection);
        Colour c = 0.4 * RayColour(newRay, objs, depth + 1);
        return 0.6 * hitData.GetColour() + c;
    }

    // Background colour
    const Vec3 direction = ray.GetDirection();
    const double y = 0.5 * (direction.y() + 1);
    const Colour startColour = Colours::BLUE;
    const Colour endColour = Colours::CYAN;
    return (1 - y) * startColour + y * endColour;
}

Ray Camera::GetRay(int w, int h)
{
    Vec3 pixelCenter = pixel0Location + w * pixelDeltaU + h * pixelDeltaV;
    Vec3 rayDirection = pixelCenter - position;
    return Ray(this->position, rayDirection);
}

void Camera::Render(std::vector<Geometry::Object *> objs)
{
    std::cout << "P3\n"
              << imageWidth << " " << imageHeight << "\n255\n";

    for (int h = 0; h < imageHeight; h++)
    {
        std::clog << "Scanlines remaining: " << h << '\n'
                  << std::flush;
        for (int w = 0; w < imageWidth; w++)
        {
            Ray ray = GetRay(w, h);
            Colour pixelColour = RayColour(ray, objs);
            pixelColour.WriteColour(std::cout);
        }
    }
}