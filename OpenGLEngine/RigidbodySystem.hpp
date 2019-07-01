#ifndef _RIGIDBODYSYSTEM_HPP
#define _RIGIDBODYSYSTEM_HPP

#include "glm/vec3.hpp"

#include "System.hpp"

class RigidbodyComponent;
class TransformComponent;
class Time;

class RigidbodySystem : public System
{
public:
	void Run(float deltaTime);
	RigidbodySystem();
private:
	std::shared_ptr<RigidbodyComponent> rbptr;
	std::shared_ptr<TransformComponent> tptr;
	Time * time;
	float lastStep;
	glm::vec3 averageAcceleration;
	void Step(float fixedDeltaTime);

	void ApplyContinousForces();

	void CalculateForces();
	
	glm::vec3 dragForce;
	glm::vec3 dragAcceleration;
	void CalculateDrag();
};
#endif // !_RIGIDBODYSYSTEM_HPP
