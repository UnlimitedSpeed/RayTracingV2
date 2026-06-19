#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "Material/Material.h"

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

public:
    WorldParser(/* args */) {};

    void CreateMaterials(nlohmann::json materials);

    void CreateCube(nlohmann::json params);
    void CreateObjects(nlohmann::json objs);
    bool CreateWorld(std::string fileName, std::vector<Geometry::Object *> &objs);
};