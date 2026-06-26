#include <string>
namespace Geometry
{
    enum class Types {
        Unknown,
        Triangle,
        Cube,
		Sphere
    };

    struct TypesConvertion {
		static Types from_string(const std::string& value) {
			if (value == "unknown") return Types::Unknown;
			if (value == "triangle") return Types::Triangle;
			if (value == "cube") return Types::Cube;
			if (value == "sphere") return Types::Sphere;
			return Types::Unknown;
		}
	};
    
}