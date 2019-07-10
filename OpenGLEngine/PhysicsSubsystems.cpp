#include "PhysicsSubsystems.hpp"

#include "TransformComponent.hpp"
#include "SpringForceComponent.hpp"
#include "Entity.hpp"

void PhysicsSubsystems::Run(float deltaTime, std::vector<std::shared_ptr<Entity>> &entities)																			
{
	PerformSpringCalculation(entities);
}

void PhysicsSubsystems::PerformSpringCalculation(std::vector<std::shared_ptr<Entity>> &entities)
{
	std::shared_ptr<SpringForceComponent> sptr;
	glm::vec3 springDelta;
	float magnitude;
	for (unsigned int x = 0; x < entities.size(); ++x)
	{
		if (sptr = entities[x]->getComp<SpringForceComponent>()) //we can assume a rigidbody and transform component
		{
			if (sptr->stype == SpringType::Connected)
			{
				springDelta = sptr->partner->position - entities[x]->getComp<TransformComponent>()->position;
			}
			else
			{
				springDelta = sptr->anchor - entities[x]->getComp<TransformComponent>()->position;
			}
			//springdelta is force in the direction we want to go
			magnitude = glm::length(springDelta);
			magnitude -= sptr->restingLength;
			magnitude *= sptr->springForce;

			entities[x]->getComp<RigidbodyComponent>()->ApplyForce(springDelta, magnitude);
		}
	}
}
