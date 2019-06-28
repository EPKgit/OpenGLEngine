#ifndef _POSITIONCOMPONENT_HPP
#define _POSITIONCOMPONENT_HPP

#include "glm/glm.hpp"

#include "Component.hpp"

class PositionComponent : public Component
{
public:
	glm::vec3 position;
};
#endif // !_POSITIONCOMPONENT_HPP
