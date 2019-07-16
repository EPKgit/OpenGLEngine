#include "RenderSystemThirdPerson.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "MeshComponent.hpp"
#include "EntityManager.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"

RenderSystemThirdPerson::RenderSystemThirdPerson()
{
	glEnable(GL_DEPTH_TEST);
	cameraUp = { 0, 1, 0 };
}

void RenderSystemThirdPerson::CalculateViewMatrix()
{
	//calculate our view model

	cameraRight = glm::normalize(glm::cross(cptr->cameraDirection, worldUp)); //find our right axis by taking world up and camera forward	
	cameraUp = glm::cross(cptr->cameraDirection, cameraRight); //calculate our camera up using our new right and forward (may be different than world up
	view = glm::lookAt(cptr->cameraOffset + ctptr->position, cptr->cameraOffset + ctptr->position + cptr->cameraDirection, worldUp);
}
void RenderSystemThirdPerson::CalculateModelMatrix()
{
	model = glm::mat4(1.0f);
	//We apply transformation in reverse order, as they will be reversed in the resulting matrix
	//Translate
	model = glm::translate(model, mtptr->position);
	////rotate on x, y, z may gimbal lock, might implement quaternions later if this becomes a problem
	model = glm::rotate(model, glm::radians(mtptr->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(mtptr->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(mtptr->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	//Scale
	model = glm::scale(model, mtptr->scale);
}

void RenderSystemThirdPerson::Run(float deltaTime)
{
	//clear screen
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::vector<std::shared_ptr<Entity>> cams = em->getEntitiesByComponents<CameraComponent, TransformComponent>();
	entities = em->getEntitiesByComponents<MeshComponent, TransformComponent>();
	for (unsigned int x = 0; x < cams.size(); ++x)
	{
		cptr = cams[x]->getComp<CameraComponent>();
		ctptr = cams[x]->getComp<TransformComponent>();


		for (unsigned int y = 0; y < entities.size(); ++y)
		{
			mcptr = entities[y]->getComp<MeshComponent>();
			mtptr = entities[y]->getComp<TransformComponent>();
			mcptr->s.Use();

			CalculateModelMatrix();
			CalculateViewMatrix();

			//attach out matrices to our shader
			mcptr->s.setMat4("model", model);
			mcptr->s.setMat4("view", view);
			mcptr->s.setMat4("projection", projection);

			for (unsigned int x = 0; x < mcptr->textures.size(); ++x)
			{
				glActiveTexture(GL_TEXTURE0 + x);
				mcptr->textures[x].Use();
			}

			glBindVertexArray(mcptr->VAO);
			if (mcptr->mType == MeshType::VertsOnly)
			{
				glDrawArrays(GL_TRIANGLES, 0, mcptr->numElements);
			}
			else if (mcptr->mType == MeshType::VertsPlusIndices)
			{
				glDrawElements(GL_TRIANGLES, mcptr->numElements, GL_UNSIGNED_INT, 0);
			}
		}
	}
}

void RenderSystemThirdPerson::DoCameraMovement(glm::vec2 inputAxis, float deltaTime)
{
	ctptr->position += inputAxis.x * cameraRight * deltaTime;
	cameraDirectionFlat = { cptr->cameraDirection.x, 0, cptr->cameraDirection.z };
	cameraDirectionFlat = glm::normalize(cameraDirectionFlat);
	ctptr->position += inputAxis.y * cameraDirectionFlat * deltaTime;
}
void RenderSystemThirdPerson::DoCameraLook(glm::vec2 inputAxis, float deltaTime)
{
	cptr->yaw += inputAxis.x * deltaTime * constants::DebugVariables::GetInstance()->lrSensitivity;
	//cptr->pitch += inputAxis.y * deltaTime * constants::DebugVariables::GetInstance()->udSensitivity;
	//cptr->pitch = cptr->pitch > 89 ? 89 : cptr->pitch < -89 ? -89 : cptr->pitch; //clamp our pitch to max 89, otherwise our view will flip weirdly
	//cptr->cameraDirection.y = sin(glm::radians(cptr->pitch));
	
	cptr->cameraOffset.x = sin(cptr->yaw) * cptr->cameraDistance;
	cptr->cameraOffset.z = -cos(cptr->yaw) * cptr->cameraDistance;
	cptr->cameraDirection = ctptr->position - (ctptr->position + cptr->cameraOffset);
	glm::normalize(cptr->cameraDirection);
}