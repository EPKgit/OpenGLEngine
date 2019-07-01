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

		ApplyContinousForces();
	
		tptr->position += rbptr->velocity * fixedDeltaTime + (0.5f * rbptr->acceleration * fixedDeltaTime * fixedDeltaTime); // velocity verlet integration
		if (tptr->position.y < 0) //if hitting the ground
		{
			tptr->position.y = 0;
			rbptr->acceleration.y = 0;
			rbptr->velocity.y = 0;
		}

		CalculateForces();
		
		rbptr->velocity += averageAcceleration * fixedDeltaTime;
		std::cout << averageAcceleration.x << " " << averageAcceleration.y << " " << averageAcceleration.z << std::endl;
	}
}

inline void RigidbodySystem::ApplyContinousForces()
{
	for (auto x = rbptr->forces.begin(); x != rbptr->forces.end();)
	{
		if ((*x).second > time->GetCurrentTime())
		{
			rbptr->acceleration += (*x).first;
			++x;
		}
		else
		{
			x = rbptr->forces.erase(x);
		}
	}
}

inline void RigidbodySystem::CalculateForces()
{
	averageAcceleration = rbptr->acceleration;
	CalculateDrag();
	averageAcceleration += rbptr->acceleration;
	averageAcceleration *= 0.5;
}

void RigidbodySystem::CalculateDrag()
{
	dragForce = 0.5f * rbptr->dragCoeff * rbptr->velocity * abs(rbptr->velocity);
	dragAcceleration = dragForce / rbptr->mass;
	rbptr->acceleration = constants::gravity - dragAcceleration;
}