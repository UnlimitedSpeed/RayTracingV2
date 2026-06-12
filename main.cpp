#include <vector>

#include "Camera/Camera.h"
#include "Geometry/Quadrilateral.h"
#include "Geometry/Cube.h"

int main()
{
    // Create Camera
    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 600;

    Camera camera = Camera(aspectRatio, imageWidth, 1.0, 2.0);

    std::vector<Geometry::Object *> objects;

    Geometry::Quadrilateral sq1 = Geometry::Quadrilateral(
        {Vec3(0, -2, -5),
         Vec3(5, -2, -4),
         Vec3(5, 1, -4),
         Vec3(0, 1, -5)},
        Colours::RED);
    objects.push_back(&sq1);

    Geometry::Quadrilateral sq2 = Geometry::Quadrilateral(
        {Vec3(0, -2, -5),
         Vec3(-5, -2, -4),
         Vec3(-5, 1, -4),
         Vec3(0, 1, -5)},
        Colours::GREEN);
    objects.push_back(&sq2);

    Geometry::Cube cube = Geometry::Cube(Vec3(0, 0, -10), 6, Colours::BLUE);
    objects.push_back(&cube);

    camera.Render(objects);

    return 0;
}