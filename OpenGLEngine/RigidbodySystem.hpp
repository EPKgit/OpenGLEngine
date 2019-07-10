#ifndef _RIGIDBODYSYSTEM_HPP
#define _RIGIDBODYSYSTEM_HPP

#include "glm/vec3.hpp"

#include "System.hpp"
#include "PhysicsSubsystems.hpp"
#include "Structs.hpp"


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
	std::vector<structs::collision> collisions;
	Time * time;
	PhysicsSubsystems subsystems;

	float lastStep;
	void Step(float fixedDeltaTime);

		void PerformMovement(float fixedDeltaTime);

			void ApplyContinousForces();
	
			void ApplyDrag();

			void ApplyDamping();

		void ResolveCollisions();

			void ResolveCollisionVelocities(int x);
		
			void ResolveCollisionOverlap(int x);
};
#endif // !_RIGIDBODYSYSTEM_HPP
