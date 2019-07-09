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
}

inline void RigidbodySystem::PerformMovement(float fixedDeltaTime)
{
	tptr->position += rbptr->velocity * fixedDeltaTime;
	if (tptr->position.y < 0)
	{
		tptr->position.y = 0;
		rbptr->velocity.y = 0;
	}
	ApplyContinousForces();
	averageAcceleration = rbptr->acceleration;
	averageAcceleration += currentFrameForce * rbptr->inverseMass;
	rbptr->velocity += averageAcceleration * fixedDeltaTime;

	rbptr->velocity *= rbptr->scaledDampingCoeff;
	//std::cout << rbptr->velocity.x << " " << rbptr->velocity.y << " " << rbptr->velocity.z << std::endl;

	currentFrameForce = constants::gravity;
}

inline void RigidbodySystem::ApplyContinousForces()
{
	for (auto x = rbptr->forces.begin(); x != rbptr->forces.end();)
	{
		if ((*x).second > time->GetCurrentTime())
  		{
			currentFrameForce += (*x).first;
			++x;
		}
		else
		{
			x = rbptr->forces.erase(x);
		}
	}
}