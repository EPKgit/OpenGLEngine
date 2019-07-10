#ifndef _FOLLOWCOMPONENT_HPP
#define _FOLLOWCOMPONENT_HPP

#include "glm/glm.hpp"

#include "Component.hpp" 

class TransformComponent;

class FollowComponent : public Component
{
public:
	FollowComponent(std::weak_ptr<Entity> e, TransformComponent * t, glm::vec3 o = { 0, 0, 0 }) : Component(e), offset(o), target(t)
	{
		type = constants::ComponentType::FollowComponent;
	}
	glm::vec3 offset;
	TransformComponent * target;
};

#endif // !_FOLLOWCOMPONENT_HPP
