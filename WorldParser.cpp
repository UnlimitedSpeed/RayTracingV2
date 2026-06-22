#include <fstream>
#include <iostream>
#include "WorldParser.h"
#include "Geometry/Structs.h"
#include "Geometry/Cube.h"

using json = nlohmann::json;

void WorldParser::CreateMaterials(nlohmann::json materials)
{
    Material *defaultMaterial = new Material();
    materialsMap.insert({"default", defaultMaterial});

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

        Material *newMaterial = new Material(colour, metallic, roughness, ior, transmission);
        materialsMap.insert({id, newMaterial});
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

void WorldParser::CreateCube(const json obj)
{
    if (!obj.contains("position"))
    {
        std::cerr << "Missing position from Cube\n";
        return;
    }
    const Vec3 pos = Vec3(
        obj["position"][0].get<double>(),
        obj["position"][1].get<double>(),
        obj["position"][2].get<double>()
    );

    if (!obj.contains("size"))
    {
        std::cerr << "Missing size from Cube\n";
        return;
    }
    const double size = obj["size"].get<double>();

    std::string mat = "default";
    if (obj.contains("material"))
    {
        mat = obj["material"];
    }

    std::unique_ptr<Geometry::Object> cube(new Geometry::Cube(pos, size, materialsMap.at(mat)));
    objectsInWorld.push_back(std::move(cube));
}

void WorldParser::CreateObjects(const json objs)
{
    std::vector<Geometry::Object *> objects;

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
        {
            CreateCube(obj);
            break;
        }
        default:
            break;
        }
    }

    return;
}

void WorldParser::CreateWorld(const std::string fileName)
{
    const auto fullName = WORLDS_FOLDER + fileName;
    std::ifstream f(fullName);
    const json data = json::parse(f);

    if (data.contains("materials") && !data["materials"].empty())
    {
        CreateMaterials(data["materials"]);
    }

    if (data.contains("lights") && !data["lights"].empty())
    {
        CreateLights(data["lights"]);
    }

    if (data.contains("objects") && !data["objects"].empty())
    {
        const auto worldObjects = data["objects"];
        objectsInWorld.clear();
        CreateObjects(worldObjects);
    }
}