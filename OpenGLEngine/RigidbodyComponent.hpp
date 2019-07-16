#ifndef _RIGIDBODYCOMPONENT_HPP
#define _RIGIDBODYCOMPONENT_HPP

#include <vector>
#include <limits>
#include <memory>

#include "glm/vec3.hpp"

#include "Component.hpp"

class TransformComponent;

class RigidbodyComponent : public Component
{
public:
	RigidbodyComponent(std::weak_ptr<Entity> e, float f = 1, glm::vec3 v = { 0, 0, 0 }, glm::vec3 a = { 0, 0, 0 });
	std::weak_ptr<TransformComponent> tptr;
	void ApplyForce(glm::vec3 direction, float amount, float duration = 0);
	std::vector<std::pair<glm::vec3, float>> forces;
	glm::vec3 velocity;
	glm::vec3 constantAcceleration;	
	glm::vec3 currentFrameForce;
	float mass;
	float inverseMass;
	float dampingCoeff;
	float scaledDampingCoeff;
	float dragCoefficient1;
	float dragCoefficient2;

	void SetInfiniteMass();
	void SetMass(float f);
	void SetDampingCoeff(float f);
private:
};
#endif // !_RIGIDBODYCOMPONENT_HPP
