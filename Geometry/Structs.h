#include <string>
namespace Geometry
{
    enum class Types {
        Unknown,
        Triangle,
        Cube
    };

    struct TypesConvertion {
		static Types from_string(const std::string& value) {
			if (value == "unknown") return Types::Unknown;
			if (value == "triangle") return Types::Triangle;
			if (value == "cube") return Types::Cube;
			return Types::Unknown;
		}

		static std::string to_string(const Types& state) {
			switch (state) {
			case Types::Unknown:
				return "unknown";
			case Types::Triangle:
				return "triangle";
            case Types::Cube:
                return "cube";
			default:
				return "unknown";
			}
		}
	};
    
}