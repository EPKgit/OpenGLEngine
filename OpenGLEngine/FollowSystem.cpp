#include "FollowSystem.hpp"

#include "FollowComponent.hpp"
#include "TransformComponent.hpp"
#include "EntityManager.hpp"

void FollowSystem::Run(float deltaTime)
{
	entities = em->getEntitiesByComponents<FollowComponent, TransformComponent>();
	for (unsigned int x = 0; x < entities.size(); ++x)
	{
		tptr = entities[x]->getComp<TransformComponent>();
		fptr = entities[x]->getComp<FollowComponent>();

		tptr->position = fptr->target->position + fptr->offset;
	}
}