#ifndef _FOLLOWCOMPONENT_HPP
#define _FOLLOWCOMPONENT_HPP

#include "glm/glm.hpp"

#include "Component.hpp" 

class PositionComponent;

class FollowComponent : public Component
{
public:
	FollowComponent();
	glm::vec3 offset;
	PositionComponent * target;
};
#endif // !_FOLLOWCOMPONENT_HPP
