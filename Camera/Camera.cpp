#include "Camera.h"
#include "helper/Vec3.h"

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

void Camera::Render()
{
    
}