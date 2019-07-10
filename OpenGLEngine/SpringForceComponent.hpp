#ifndef _SPRINGFORCECOMPONENT_HPP
#define _SPRINGFORCECOMPONENT_HPP

#include <memory>

#include "glm/vec3.hpp"

#include "Component.hpp"

class TransformComponent;

enum class SpringType
{
	Fixed, Connected
};

class SpringForceComponent : public Component
{
public:
	SpringForceComponent(std::weak_ptr<Entity> e, std::shared_ptr<TransformComponent> p, float sf = 1.0f, float rl = 1.0f)
		:	Component(e), stype(SpringType::Connected), partner(p), springForce(sf), restingLength(rl)
	{
		type = constants::ComponentType::SpringForceComponent;
	}
	SpringForceComponent(std::weak_ptr<Entity> e, glm::vec3 f, float sf = 1.0f, float rl = 1.0f)
		: Component(e), stype(SpringType::Fixed), anchor(f), springForce(sf), restingLength(rl) 
	{ 
		type = constants::ComponentType::SpringForceComponent;
	}
	SpringType stype;
	std::shared_ptr<TransformComponent> partner;
	glm::vec3 anchor;
	float springForce;
	float restingLength;
private:
};
#endif // !_SPRINGFORCECOMPONENT_HPP
