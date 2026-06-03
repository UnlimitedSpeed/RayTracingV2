#include "Camera.h"

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

Colour Camera::RayColour(const Ray& ray)
{
    // Background colour
    const Vec3 direction = ray.GetDirection();
    const double y = 0.5 * (direction.y() + 1);
    const Colour startColour = Colours::BLUE;
    const Colour endColour = Colours::CYAN;
    return (1 - y) * startColour + y * endColour;
}

Ray Camera::GetRay(int w, int h)
{
    Vec3 pixelCenter = pixel0Location + w * pixelDeltaU + h  * pixelDeltaV;
    Vec3 rayDirection = pixelCenter - position;
    return Ray(this->position, rayDirection);
}

void Camera::Render()
{
    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    for (int h = 0; h < imageHeight; h++)
    {
        for (int w = 0; w < imageWidth; w++)
        {
            Ray ray = GetRay(w, h);
            Colour pixelColour = RayColour(ray);
            pixelColour.WriteColour(std::cout);
        }
    }
    
}