#include <iostream>
#include "Camera/Camera.h"

int main () {
    std::clog << "Hello, World!" << std::endl;
    // Create Camera
    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 600;

    Camera camera = Camera(aspectRatio, imageWidth, 1.0, 2.0);

    camera.Render();

    return 0;
}