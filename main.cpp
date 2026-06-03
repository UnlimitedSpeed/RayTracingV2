#include <iostream>
#include <vector>
#include "Camera/Camera.h"
#include "Geometry/Object.h"
#include "Geometry/Quadrilateral.h"

int main () {
    std::clog << "Hello, World!" << std::endl;
    // Create Camera
    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 600;

    Camera camera = Camera(aspectRatio, imageWidth, 1.0, 2.0);

    std::vector<Geometry::Object*> objects;

    Geometry::Quadrilateral sq1 = Geometry::Quadrilateral(
        Vec3(0, 0, 0),
        Vec3(1, 0, 0),
        Vec3(1, 1, 0),
        Vec3(0, 1, 0)
    );
    objects.push_back(&sq1);

    camera.Render(objects);

    return 0;
}