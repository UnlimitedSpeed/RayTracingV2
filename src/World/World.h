#ifndef WORLD_HPP
#define WORLD_HPP

#include <map>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
 #include "src/Material/Material.h"
#include "src/helper/Vec3.h"

namespace Geometry
{
    class Object;
    class Cube;
    enum class Types;
    struct TypesConvertion;    
}

class World
{
private:
    /* data */
    std::string WORLDS_FOLDER = "worlds/";
    std::vector<std::unique_ptr<Geometry::Object>> objectsInWorld;
    std::map<std::string, std::unique_ptr<Material>> materialsMap;
    std::vector<Vec3> lightsInWorld;

public:
    World() {};

    const std::vector<std::unique_ptr<Geometry::Object>>& GetObjects() const { return objectsInWorld; };
    const std::vector<Vec3>& GetLights() const { return lightsInWorld; };

    void CreateMaterials(nlohmann::json materials);
    void CreateLights(nlohmann::json lights);
    void CreateCube(nlohmann::json object);
    void CreateSphere(nlohmann::json object);
    void CreateCubicSphere(nlohmann::json object);
    void CreateTriangle(nlohmann::json object);
    void CreateObjects(nlohmann::json objs);
    void CreateWorld(std::string fileName);
};

#endif