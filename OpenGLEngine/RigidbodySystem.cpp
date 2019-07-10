#include "RigidbodySystem.hpp"

#include <iostream>

#include "Structs.hpp"
#include "Time.hpp"
#include "EntityManager.hpp"
#include "TransformComponent.hpp"
#include "RigidbodyComponent.hpp"


RigidbodySystem::RigidbodySystem()
{
	time = Time::GetInstance();
	lastStep = time->GetCurrentTime();
}

void RigidbodySystem::Run(float deltaTime)
{
	entities = em->getEntitiesByComponents<RigidbodyComponent, TransformComponent>();
	while (lastStep < time->GetCurrentTime())
	{
		Step(constants::fixedTimeStep);
		lastStep += constants::fixedTimeStep;
	}
}

void RigidbodySystem::Step(float fixedDeltaTime)
{
	for (unsigned int x = 0; x < entities.size(); ++x)
	{
		rbptr = entities[x]->getComp<RigidbodyComponent>();
		tptr = entities[x]->getComp<TransformComponent>();
		PerformMovement(fixedDeltaTime);
		//CheckCollisions
		//ResolveCollisions
	}
	subsystems.Run(fixedDeltaTime, entities);
}

inline void RigidbodySystem::PerformMovement(float fixedDeltaTime)
{
	tptr->position += rbptr->velocity * fixedDeltaTime;
	/*if (tptr->position.y < 0)
	{
		tptr->position.y = 0;
		rbptr->velocity.y = 0;
	}*/

	ApplyContinousForces(); //apply forces that are applied over multiple frames stores in currentFrameForce
	ApplyDrag(); //calculate our drag force, will counteract some of our currentFrameForce

	glm::vec3 currentFrameAcceleration = rbptr->constantAcceleration; //we don't want to affect constant acceleration
	currentFrameAcceleration += rbptr->currentFrameForce * rbptr->inverseMass; //F = ma | a = F * (1 / m)
	rbptr->velocity += currentFrameAcceleration * fixedDeltaTime; //we need to create framerate independence

	 //perform damping//
	//std::cout << rbptr->velocity.x << " " << rbptr->velocity.y << " " << rbptr->velocity.z << std::endl;

	rbptr->currentFrameForce = constants::gravity;
}

inline void RigidbodySystem::ApplyContinousForces()
{
	for (auto x = rbptr->forces.begin(); x != rbptr->forces.end();)
	{
		if ((*x).second > time->GetCurrentTime())
  		{
			rbptr->currentFrameForce += (*x).first;
			++x;
		}
		else
		{
			x = rbptr->forces.erase(x);
		}
	}
}

inline void RigidbodySystem::ApplyDamping()
{
	rbptr->velocity *= rbptr->scaledDampingCoeff;
}

void RigidbodySystem::ResolveCollisions()
{
	
	for (unsigned int x = 0; x < collisions.size(); ++x)
	{
		ResolveCollisionVelocities(x);
		ResolveCollisionOverlap(x);
	}
}

void RigidbodySystem::ResolveCollisionVelocities(int x)
{
	glm::vec3 impulseVector;
	glm::vec3 combinedVelocityVector;
	float seperatingForceScalar;
	float totalInverseMass;
	combinedVelocityVector = collisions[x].a->velocity;
	//only add the second one if it exists
	combinedVelocityVector = (collisions[x].b) ? collisions[x].b->velocity + combinedVelocityVector : combinedVelocityVector;
	seperatingForceScalar = glm::dot(combinedVelocityVector, collisions[x].collisionNormal);
	if (seperatingForceScalar > 0)//our seperating force should be negative as it should be pushing away from b rather than towards is
	{
		return;
	}
	seperatingForceScalar *= -2.0f * collisions[x].restitutionCoeff;
	totalInverseMass = collisions[x].a->inverseMass;
	totalInverseMass += (collisions[x].b) ? collisions[x].b->inverseMass : 0; //only add in the second mass if it exists
	if (totalInverseMass <= 0) //if they both have infinite mass then there's no reason to apply force to either
	{
		return;
	}
	impulseVector = collisions[x].collisionNormal * seperatingForceScalar / totalInverseMass;
	collisions[x].a->velocity += impulseVector * collisions[x].a->inverseMass;
	if (collisions[x].b)
	{
		collisions[x].b->velocity += -impulseVector * collisions[x].b->inverseMass; //we want to apply the force in the other direction
	}
}

void RigidbodySystem::ResolveCollisionOverlap(int x)
{
	float totalInverseMass;
	glm::vec3 movementRequired;
	if (collisions[x].overlapAmount <= 0) //if we aren't even overlapping why bother
	{
		return;
	}
	totalInverseMass = collisions[x].a->inverseMass;
	totalInverseMass += collisions[x].b ? collisions[x].b->inverseMass : 0;
	if (totalInverseMass <= 0)//if they both have inverse mass then just ignore their collision
	{
		return;
	}
	movementRequired = collisions[x].collisionNormal * (collisions[x].overlapAmount / totalInverseMass);

	//collisions[x].a->

}

inline void RigidbodySystem::ApplyDrag()
{
	glm::vec3 dragForce = rbptr->velocity; //drag is based on velocity
	float dragAmount = glm::length(dragForce);
	if (dragAmount == 0) //if we have no velocity we don't need to calculate drag
	{
		return;
	}
	dragAmount = rbptr->dragCoefficient1 * dragAmount + rbptr->dragCoefficient2 * dragAmount * dragAmount;
	dragForce = glm::normalize(dragForce); //create a direction vector
	dragForce *= -dragAmount; //we need to go negative, as we need a reverse our direction vector to oppose our velocity
	rbptr->currentFrameForce += dragForce * rbptr->inverseMass;
}
