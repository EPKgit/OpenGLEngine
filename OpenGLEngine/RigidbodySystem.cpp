#include "RigidbodySystem.hpp"

#include <iostream>

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
	CalculateDrag(); //calculate our drag force, will counteract some of our currentFrameForce

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

inline void RigidbodySystem::CalculateDamping()
{
	rbptr->velocity *= rbptr->scaledDampingCoeff;
}

inline void RigidbodySystem::CalculateDrag()
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