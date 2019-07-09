#ifndef _RIGIDBODYCOMPONENT_HPP
#define _RIGIDBODYCOMPONENT_HPP

#include <vector>
#include <limits>

#include "glm/vec3.hpp"

#include "Component.hpp"

class RigidbodyComponent : public Component
{
public:
	RigidbodyComponent(float f = 1, glm::vec3 v = { 0, 0, 0 }, glm::vec3 a = { 0, 0, 0 });
	void ApplyForce(glm::vec3 direction, float amount, float duration = 0);
	std::vector<std::pair<glm::vec3, float>> forces;
	glm::vec3 velocity;
	glm::vec3 acceleration;	
	float mass;
	float inverseMass;
	float dampingCoeff;
	float scaledDampingCoeff;

	void SetInfiniteMass() 
	{ 
		inverseMass = 0; 
		mass = std::numeric_limits<float>::max(); 
	}
	void SetMass(float f)
	{
		mass = f;
		inverseMass = 1.0f / f;
	}
	void SetDampingCoeff(float f)
	{
		dampingCoeff = f;
		scaledDampingCoeff = powf(dampingCoeff, constants::fixedTimeStep);
	}
	
private:
};
#endif // !_RIGIDBODYCOMPONENT_HPP
