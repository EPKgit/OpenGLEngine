#include "PlayerMovementSystem.hpp"

#include "EntityManager.hpp"
#include "PlayerMovementComponent.hpp"
#include "InputComponent.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"

void PlayerMovementSystem::Run(float deltaTime)
{
	entities = em->getEntitiesByComponents<PlayerMovementComponent, CameraComponent, TransformComponent>();
	std::shared_ptr<InputComponent> iptr = em->getSingletonEntity()->getComp<InputComponent>();
	std::shared_ptr<TransformComponent> tptr;
	std::shared_ptr<CameraComponent> cptr;
	glm::vec3 cameraDirectionFlat;
	for (unsigned int x = 0; x < entities.size(); ++x)
	{
		tptr = entities[x]->getComp<TransformComponent>();
		cptr = entities[x]->getComp<CameraComponent>();
		if (iptr->moveAxis.x != 0 || iptr->moveAxis.y != 0)
		{
			cptr->dirty = true;
			tptr->position += iptr->moveAxis.x * cptr->cameraRight * deltaTime;
			cameraDirectionFlat = { cptr->cameraDirection.x, 0, cptr->cameraDirection.z };
			cameraDirectionFlat = glm::normalize(cameraDirectionFlat);
			tptr->position += iptr->moveAxis.y * cameraDirectionFlat * deltaTime;
		}
	}
}
