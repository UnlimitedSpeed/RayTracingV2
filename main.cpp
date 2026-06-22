#include <vector>

#include "Camera/Camera.h"
#include "Geometry/Cube.h"
#include "WorldParser.h"

int main(int argc, char** argv)
{
    // Create Camera
    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 600;

    Camera camera = Camera(aspectRatio, imageWidth, 1.0, 2.0);

    WorldParser wp = WorldParser();

    wp.CreateWorld(argv[1]);
    camera.Render(wp.GetObjectsInWorld(), wp.GetLightsInWorld());

    return 0;
}