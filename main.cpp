#include <vector>
#include <SDL2/SDL.h>

#include "Camera/Camera.h"
#include "Geometry/Cube.h"
#include "WorldParser.h"

int main(int argc, char** argv)
{
    // Create Camera
    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 600;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(imageWidth, imageWidth/aspectRatio, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    Camera camera = Camera(aspectRatio, imageWidth, 1.0, 2.0);

    WorldParser wp = WorldParser();

    wp.CreateWorld(argv[1]);

    bool running = true;
    camera.Render(renderer, wp.GetObjectsInWorld(), wp.GetLightsInWorld(), running);

    while (running)
    {
        SDL_Event event;
        if (!SDL_WaitEvent(&event))
            break;
        if (event.type == SDL_QUIT)
            running = false;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}