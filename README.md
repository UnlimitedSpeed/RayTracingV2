# Raytracer

This is a small raytracing project, written in C++.

This project uses the [SDL3](https://github.com/libsdl-org/SDL) and the [nlohmann/json](https://github.com/nlohmann/json) libraries.

The main objective of this project is to practice the C++ language, not to create an efficient and optimized ray tracer.

> Important disclaimer:
> This program runs on the CPU so it is slow. Older CPUs might struggle to run the program.

## Worlds

In order to create a render of something, we need a world to be rendered. Worlds are simple JSON files containing the necessary information: materials, lights, and objects.

Here is a simple example of a world containing a single white cube:

```json
{
    "materials":
    [
        {
            "id": "WhiteSolid",
            "colour": [255, 255, 255],
            "metallic": 0,
            "roughness": 1,
            "transmission": 0
        }
    ],
    "lights":
    [
        {
            "position": [1, 1, 1]
        }
    ],
    "objects":
    [
        {
            "type": "cube",
            "position": [0, 0, -10],
            "size": 5,
            "material": "WhiteSolid"
        }
    ]
}
```

### Materials

* The *id* is mandatory, if no *id* is found the material will be ignored and any object that uses it will be given a default material.
* The *colour* represents the colour of the material. Values go from 0 to 255, each representing a primary colour: *red*, *green*, *blue*. If no colour is provided the material will be black.
* Explanation for the remaining 3 arguments can be found [here](https://lighttracer.org/blog/tutorial-materials/).

### Lights

* The lights only have one argument representing their position in the world.

### Objects

Currently there are 4 different possible objects: Triangle, Cube, Sphere, CubeSphere. As the name suggests, the Sphere and the CubeSphere both create a sphere but use different processes.

To create an object, first the correct type must be given: *triangle*, *cube*, *sphere*, *cube_sphere*, respectively.

* Triangle:
  * *vertices*: an array with 3 arrays, each representing a vertice of the triangle.
  * ```json
    {
      "type": "triangle",
      "vertices":
        [[0, 0, -10],
        [1, 0, -10],
        [0, 1, -10]],
      "material": "WhiteSolid"
    }
    ```
* Cube:
  * *position*: the center position of the cube.
  * "size*: the size of the cube's edge
  * ```json
    {
      "type": "cube",
      "position": [0, 0, -10],
      "size": 5,
      "material": "WhiteSolid"
    }
    ```
* Sphere:
  * *position*: the center position of the sphere.
  * *radius*: the radius of the sphere.
  * *sides*: the number of divisions going around the sphere. The higher the number the more detailed it is.
  * *height*: the number of divisions from top to bottom. The higher the number the more detailed it is.
  * ```json
    {
      "type": "cube",
      "position": [0, 0, -10],
      "radius": 5,
      "sides": 10,
      "height": 10,
      "material": "WhiteSolid"
    }
    ```
* CubeSphere:
  * *position*: the center position of the sphere.
  * *radius*: the radius of the sphere.
  * *subdivisions*: the number of times each face of the cube is divided before being made into a sphere. The higher the number the more detailed it is.
  * ```json
    {
      "type": "cube_sphere",
      "position": [0, 5, -7],
      "radius": 2,
      "subdivisions": 10,
      "material": "RedSolid"
    }
    ```

















