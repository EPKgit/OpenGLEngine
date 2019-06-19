#include "Structs.hpp"

std::ostream& structs::operator<<(std::ostream& out, const structs::vec3d &v)
{
	out << v.x << " " << v.y << " " << v.z;
	return out;
}