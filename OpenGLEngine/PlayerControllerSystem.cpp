#include "PlayerControllerSystem.hpp"

#include "EntityManager.hpp"
#include "PlayerControllerComponent.hpp"
#include "InputComponent.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"

void PlayerControllerSystem::Run(float deltaTime)
{
	entities = em->getEntitiesByComponents<PlayerControllerComponent, CameraComponent, TransformComponent>();
	std::shared_ptr<InputComponent> iptr = em->getSingletonEntity()->getComp<InputComponent>();
	std::shared_ptr<TransformComponent> tptr;
	std::shared_ptr<CameraComponent> cptr;
	std::shared_ptr<PlayerControllerComponent> pcptr;
	glm::vec3 cameraDirectionFlat;
	for (unsigned int x = 0; x < entities.size(); ++x)
	{
		tptr = entities[x]->getComp<TransformComponent>();
		cptr = entities[x]->getComp<CameraComponent>();
		pcptr = entities[x]->getComp<PlayerControllerComponent>();
		if (iptr->moveAxis.x != 0 || iptr->moveAxis.y != 0)
		{
			cptr->dirty = true;
			tptr->position += iptr->moveAxis.x * cptr->cameraRight * deltaTime * pcptr->movementSpeed;
			cameraDirectionFlat = { cptr->cameraDirection.x, 0, cptr->cameraDirection.z };
			cameraDirectionFlat = glm::normalize(cameraDirectionFlat);
			tptr->position += iptr->moveAxis.y * cameraDirectionFlat * deltaTime * pcptr->movementSpeed;
		}
		CameraLookFPS(deltaTime, iptr, tptr, cptr, pcptr);
	}
}

void PlayerControllerSystem::CameraLookFPS(	float deltaTime, std::shared_ptr<InputComponent> iptr, std::shared_ptr<TransformComponent> tptr, 
											std::shared_ptr<CameraComponent> cptr, std::shared_ptr<PlayerControllerComponent> pcptr)
{
	if (iptr->mouseAxis.x != 0 || iptr->mouseAxis.y != 0)
	{
		cptr->dirty = true;
		cptr->yaw += iptr->mouseAxis.x * deltaTime * pcptr->hSens;
		cptr->pitch += iptr->mouseAxis.y * deltaTime * pcptr->vSens;
		cptr->pitch = cptr->pitch > 89 ? 89 : cptr->pitch < -89 ? -89 : cptr->pitch; //clamp our pitch to max 89, otherwise our view will flip weirdly
		cptr->cameraDirection.y = sin(glm::radians(cptr->pitch));
		cptr->cameraDirection.z = -cos(glm::radians(cptr->yaw));
		cptr->cameraDirection.x = sin(glm::radians(cptr->yaw));
		cptr->cameraDirection = glm::normalize(cptr->cameraDirection);
	}
}

void PlayerControllerSystem::CameraLookTPS(	float deltaTime, std::shared_ptr<InputComponent> iptr, std::shared_ptr<TransformComponent> tptr, 
											std::shared_ptr<CameraComponent> cptr, std::shared_ptr<PlayerControllerComponent> pcptr)
{
	cptr->yaw += iptr->mouseAxis.x * deltaTime * pcptr->hSens;

	cptr->cameraOffset.x = sin(cptr->yaw) * cptr->cameraDistance;
	cptr->cameraOffset.z = -cos(cptr->yaw) * cptr->cameraDistance;
	cptr->cameraDirection = tptr->position - (tptr->position + cptr->cameraOffset);
	cptr->cameraDirection = glm::normalize(cptr->cameraDirection);
}
