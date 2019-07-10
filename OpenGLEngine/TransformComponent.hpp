#ifndef _POSITIONCOMPONENT_HPP
#define _POSITIONCOMPONENT_HPP

#include "glm/glm.hpp"

#include "Component.hpp"
#include "Constants.hpp"

class TransformComponent : public Component
{
public:
	TransformComponent(std::weak_ptr<Entity> e, glm::vec3 p = { 0, 0, 0 }, glm::vec3 r = { 0, 0, 0 }, glm::vec3 s = { 1, 1, 1 });
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};
#endif // !_POSITIONCOMPONENT_HPP
