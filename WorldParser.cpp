#include <fstream>
#include <iostream>
#include "WorldParser.h"
#include "Geometry/Structs.h"
#include "Geometry/Cube.h"

using json = nlohmann::json;

void WorldParser::CreateCube(const json params)
{
    if (!params.contains("position"))
    {
        std::cerr << "Missing position from Cube\n";
        return;
    }
    const Vec3 pos = Vec3(params["position"][0], params["position"][1], params["position"][2]);

    if (!params.contains("size"))
    {
        std::cerr << "Missing size from Cube\n";
        return;
    }
    const double size = params["size"];

    std::unique_ptr<Geometry::Object> cube(new Geometry::Cube(pos, size, Colour()));
    objectsInWorld.push_back(std::move(cube));
    return;
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

        if (!obj.contains("params"))
        {
            std::cerr << "Missing parameters\n";
            continue;
        }
        const json params = obj["params"];
        
        switch (type)
        {
            case Geometry::Types::Cube:
            {
                CreateCube(params);
                break;
            }
            default:
                break;
        }
    }

    return;
}

bool WorldParser::CreateWorld(const std::string fileName, std::vector<Geometry::Object *> &objects)
{
    const auto fullName = WORLDS_FOLDER + fileName;
    std::ifstream f(fullName);
    const json data = json::parse(f);

    objectsInWorld.clear();

    if (!data.contains("objects"))
    {
        std::cerr << "No Objects found on file" << std::endl;
        return false;
    }

    const auto worldObjects = data["objects"];
    CreateObjects(worldObjects);
    objects.clear();
    for (auto &o : objectsInWorld)
    {
        objects.push_back(o.get());
    }

    return true;
}