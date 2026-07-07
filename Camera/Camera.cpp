#include <cmath>
#include <iostream>
#include <chrono>

#include "Camera.h"
#include "Geometry/Object.h"
#include "helper/Utils.h"

Camera::Camera(double aspectRatio, int imageWidth, double focalLength, double viewportHeight)
{
    this->aspectRatio = aspectRatio;
    this->imageWidth = imageWidth;
    this->imageHeight = int(imageWidth / aspectRatio);

    this->focalLength = focalLength;
    this->viewportHeight = viewportHeight;
    this->viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    this->position = Vec3(0, 3, 0);

    this->viewportU = Vec3(viewportWidth, 0, 0);
    this->viewportV = Vec3(0, -viewportHeight, 0);

    this->pixelDeltaU = viewportU / imageWidth;
    this->pixelDeltaV = viewportV / imageHeight;

    this->viewportUpperLeft = position - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
    this->pixel0Location = viewportUpperLeft + pixelDeltaU / 2 + pixelDeltaV / 2;
}

bool Camera::HitInterval(const Ray &ray, const std::vector<std::unique_ptr<Geometry::Object>> &objs, HitData &hitData)
{
    HitData hitTemp;

    bool isHit = false;

    const double minT = 0.001;
    double closestT = MAX_INTERVAL;

    for (auto &obj : objs)
    {
        if (obj->Hit(ray, hitTemp, {minT, closestT}))
        {
            isHit = true;
            closestT = hitTemp.GetT();
            hitData = hitTemp;
        }
    }
    return isHit;
}

Colour Camera::RayColour(const Ray &ray, const std::vector<std::unique_ptr<Geometry::Object>> &objs, const std::vector<Vec3> &lights, int depth)
{
    if (depth > maxDepth)
    {
        return Colour();
    }

    HitData hitData;
    if (HitInterval(ray, objs, hitData))
    {
        Colour diffuse = hitData.GetMaterial()->GetColour() * 0.2;
        for (auto l : lights)
        {
            Vec3 toLight = l - hitData.GetPoint();
            const double lightDistance = toLight.Length();
            const Vec3 lightDirection = (toLight).UnitVector();
            const double dot = std::max(0.0, lightDirection.Dot(hitData.GetNormal()));

            const Ray shadowRay = Ray(hitData.GetPoint() + hitData.GetNormal() * 0.001, lightDirection);
            HitData tmp;
            if (HitInterval(shadowRay, objs, tmp))
            {
                if (tmp.GetT() < lightDistance)
                {
                    continue;
                }
            }

            diffuse += hitData.GetMaterial()->GetColour() * Colours::WHITE * dot;
        }

        Vec3 newDirection = ray.GetDirection() - 2 * ray.GetDirection().Dot(hitData.GetNormal()) * hitData.GetNormal();
        Ray newRay = Ray(hitData.GetPoint(), newDirection);

        return diffuse + 0.1 * RayColour(newRay, objs, lights, depth + 1);
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
    auto offset = SampleSquare();

    Vec3 pixelCenter = pixel0Location + (w + offset.x()) * pixelDeltaU + (h + offset.y()) * pixelDeltaV;
    Vec3 rayDirection = pixelCenter - position;
    return Ray(this->position, rayDirection);
}

Vec3 Camera::SampleSquare()
{
    return Vec3(random_double() - 0.1, random_double() - 0.1, 0);
}

void Camera::DrawBuffer(SDL_Renderer *renderer, const std::vector<Colour> &colourBuffer) const
{
    for (int h = 0; h < imageHeight; h++)
    {
        for (int w = 0; w < imageWidth; w++)
        {
            const auto colour = colourBuffer[h * imageWidth + w].GetColourToWrite();
            SDL_SetRenderDrawColor(renderer, colour[0], colour[1], colour[2], 255);
            SDL_RenderDrawPoint(renderer, w, h);
        }
    }
}

void Camera::ThreadColour(const std::vector<std::unique_ptr<Geometry::Object>> &objs, const std::vector<Vec3> &lights, std::vector<Colour> &colourBuffer, const int lowerBound, const int upperBound, std::atomic<int> &finishedThreads)
{
    for (int h = lowerBound; h < upperBound; h++)
    {
        for (int w = 0; w < imageWidth; w++)
        {
            Colour pixelColour(0, 0, 0);
            for (int sample = 0; sample < samples_per_pixel; sample++)
            {
                Ray ray = GetRay(w, h);
                pixelColour += RayColour(ray, objs, lights, 0);
            }
            pixelColour = pixelColour / samples_per_pixel;
            colourBuffer[h * imageWidth + w] = pixelColour;
        }
    }
    finishedThreads++;
}

void Camera::Render(SDL_Renderer *renderer, const std::vector<std::unique_ptr<Geometry::Object>> &objs, const std::vector<Vec3> &lights, bool &running)
{
    const int nThreads = 16;
    const int dividedHeight = imageHeight / nThreads;
    std::vector<std::thread> threads;
    std::vector<Colour> colourBuffer(imageHeight * imageWidth);
    std::atomic<int> finishedThreads{0};

    for (int i = 0; i < nThreads; i++)
    {
        const int lowerBound = dividedHeight * i;
        const int upperBound = (i == nThreads - 1) ? imageHeight : dividedHeight * (i + 1);
        threads.emplace_back(
            &Camera::ThreadColour,
            this,
            std::ref(objs),
            std::ref(lights),
            std::ref(colourBuffer),
            lowerBound,
            upperBound,
            std::ref(finishedThreads)
        );
        }

    while (finishedThreads < nThreads && running)
    {
        DrawBuffer(renderer, colourBuffer);
        SDL_RenderPresent(renderer);

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    for (auto &t : threads)
    {
        if (t.joinable())
            t.join();
    }

    if (running)
    {
        DrawBuffer(renderer, colourBuffer);
        SDL_RenderPresent(renderer);
    }

    std::clog << "\nDone.\n";
}