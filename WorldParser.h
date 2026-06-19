#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

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

public:
    WorldParser(/* args */) {};

    void CreateCube(nlohmann::json params);
    void CreateObjects(nlohmann::json objs);
    bool CreateWorld(std::string fileName, std::vector<Geometry::Object *> &objs);
};