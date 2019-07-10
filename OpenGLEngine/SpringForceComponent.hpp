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
	SpringForceComponent(std::shared_ptr<TransformComponent> p, float sf = 1.0f, float rl = 1.0f) 
		: stype(SpringType::Connected), partner(p), springForce(sf), restingLength(rl) { }
	SpringForceComponent(glm::vec3 f, float sf = 1.0f, float rl = 1.0f)
		: stype(SpringType::Fixed), anchor(f), springForce(sf), restingLength(rl) { }
	SpringType stype;
	std::shared_ptr<TransformComponent> partner;
	glm::vec3 anchor;
	float springForce;
	float restingLength;
private:
	SpringForceComponent() { type = constants::ComponentType::SpringForceComponent; }
};
#endif // !_SPRINGFORCECOMPONENT_HPP
