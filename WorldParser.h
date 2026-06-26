#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "Material/Material.h"
#include "helper/Vec3.h"

namespace Geometry
{
    class Object;
    class Cube;
    enum class Types;
    struct TypesConvertion;    
}

class WorldParser
{
private:
    /* data */
    std::string WORLDS_FOLDER = "worlds/";
    std::vector<std::unique_ptr<Geometry::Object>> objectsInWorld;
    std::map<std::string, Material*> materialsMap;
    std::vector<Vec3> lightsInWorld;

public:
    WorldParser(/* args */) {};

    const std::vector<std::unique_ptr<Geometry::Object>>& GetObjectsInWorld() const { return objectsInWorld; };
    const std::vector<Vec3>& GetLightsInWorld() const { return lightsInWorld; };

    void CreateMaterials(nlohmann::json materials);
    void CreateLights(nlohmann::json lights);
    void CreateCube(nlohmann::json object);
    void CreateSphere(nlohmann::json object);
    void CreateObjects(nlohmann::json objs);
    void CreateWorld(std::string fileName);
};