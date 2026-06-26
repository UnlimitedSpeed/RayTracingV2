#include <fstream>
#include <iostream>
#include <memory>
#include "WorldParser.h"
#include "Geometry/Structs.h"
#include "Geometry/Cube.h"
#include "Geometry/Sphere.h"
#include "Geometry/TriangleObject.h"

using json = nlohmann::json;

void WorldParser::CreateMaterials(nlohmann::json materials)
{
    materialsMap.emplace("default", std::make_unique<Material>());

    for (auto mat : materials)
    {
        if (!mat.contains("id"))
        {
            std::cerr << "Missing id from material\n";
            continue;
        }
        const std::string id = mat["id"];

        Colour colour = Colour();
        if (mat.contains("colour"))
        {
            auto c = mat["colour"];
            colour = Colour(
                c[0].get<double>() / 255.0,
                c[1].get<double>() / 255.0,
                c[2].get<double>() / 255.0
            );
        }

        float metallic = 0;
        if (mat.contains("metallic"))
        {
            metallic = mat["metallic"].get<float>();
        }

        float roughness = 1;
        if (mat.contains("roughness"))
        {
            roughness = mat["roughness"].get<float>();
        }

        float ior = 0;
        if (mat.contains("ior"))
        {
            ior = mat["ior"].get<float>();
        }

        float transmission = 0;
        if (mat.contains("transmission"))
        {
            transmission = mat["transmission"].get<float>();
        }

        materialsMap.emplace(id, std::make_unique<Material>(colour, metallic, roughness, ior, transmission));
    }
}

void WorldParser::CreateLights(const json lights)
{
    for (auto light : lights)
    {
        if (!light.contains("position"))
        {
            std::cerr << "Missing position for light\n";
            continue;
        }

        const Vec3 pos = Vec3(
            light["position"][0].get<double>(),
            light["position"][1].get<double>(),
            light["position"][2].get<double>()
        );
        lightsInWorld.push_back(pos);
    }
}

void WorldParser::CreateCube(const json object)
{
    if (!object.contains("position"))
    {
        std::cerr << "Missing position from Cube\n";
        return;
    }
    const Vec3 pos = Vec3(
        object["position"][0].get<double>(),
        object["position"][1].get<double>(),
        object["position"][2].get<double>()
    );

    if (!object.contains("size"))
    {
        std::cerr << "Missing size from Cube\n";
        return;
    }
    const double size = object["size"].get<double>();

    std::string mat = "default";
    if (object.contains("material"))
    {
        mat = object["material"];
    }

    objectsInWorld.push_back(std::make_unique<Geometry::Cube>(pos, size, materialsMap.at(mat).get()));
}

void WorldParser::CreateSphere(const json object)
{
    if (!object.contains("position"))
    {
        std::cerr << "Missing position for Sphere\n";
        return;
    }
    const Vec3 pos = Vec3(
        object["position"][0].get<double>(),
        object["position"][1].get<double>(),
        object["position"][2].get<double>()
    );

    if (!object.contains("radius"))
    {
        std::cerr << "Missing radius for Sphere\n";
        return;
    }
    const int radius = object["radius"].get<int>();

    if (!object.contains("sides"))
    {
        std::cerr << "Missing sides for Sphere\n";
        return;
    }
    const int sides = object["sides"].get<int>();

    if (!object.contains("height"))
    {
        std::cerr << "Missing height for Sphere\n";
        return;
    }
    const int height = object["height"].get<int>();

    std::string mat = "default";
    if (object.contains("material"))
    {
        mat = object["material"];
    }

    objectsInWorld.push_back(std::make_unique<Geometry::Sphere>(pos, radius, sides, height, materialsMap.at(mat).get()));
}

void WorldParser::CreateTriangle(const json object)
{
    if (!object.contains("vertices"))
    {
        std::cerr << "Missing vertices from Triangle\n";
        return;
    }

    const auto &verts = object["vertices"];
    if (verts.size() != 3)
    {
        std::cerr << "Triangle must have exactly 3 vertices\n";
        return;
    }

    const Vec3 v0(
        verts[0][0].get<double>(),
        verts[0][1].get<double>(),
        verts[0][2].get<double>()
    );
    const Vec3 v1(
        verts[1][0].get<double>(),
        verts[1][1].get<double>(),
        verts[1][2].get<double>()
    );
    const Vec3 v2(
        verts[2][0].get<double>(),
        verts[2][1].get<double>(),
        verts[2][2].get<double>()
    );

    std::string mat = "default";
    if (object.contains("material"))
    {
        mat = object["material"];
    }

    objectsInWorld.push_back(std::make_unique<Geometry::TriangleObject>(
        Geometry::Triangle(v0, v1, v2),
        materialsMap.at(mat).get()
    ));
}

void WorldParser::CreateObjects(const json objs)
{
    for (auto obj : objs)
    {
        if (!obj.contains("type"))
        {
            std::cerr << "Missing type\n";
            continue;
        }
        const Geometry::Types type = Geometry::TypesConvertion::from_string(obj["type"]);

        switch (type)
        {
        case Geometry::Types::Cube:
            CreateCube(obj);
            break;
        case Geometry::Types::Sphere:
            CreateSphere(obj);
            break;
        case Geometry::Types::Triangle:
            CreateTriangle(obj);
            break;
        default:
            break;
        }
    }
}

void WorldParser::CreateWorld(const std::string fileName)
{
    const auto fullName = WORLDS_FOLDER + fileName;
    std::ifstream f(fullName);
    const json data = json::parse(f);

    materialsMap.clear();
    lightsInWorld.clear();
    objectsInWorld.clear();

    if (data.contains("materials") && !data["materials"].empty())
    {
        CreateMaterials(data["materials"]);
    }
    else
    {
        materialsMap.emplace("default", std::make_unique<Material>());
    }

    if (data.contains("lights") && !data["lights"].empty())
    {
        CreateLights(data["lights"]);
    }

    if (data.contains("objects") && !data["objects"].empty())
    {
        CreateObjects(data["objects"]);
    }
}