#include "RenderSystem.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "MeshComponent.hpp"
#include "EntityManager.hpp"

RenderSystem::RenderSystem()
{
	projection = glm::perspective(glm::radians(constants::fieldOfView), constants::aspectRatio, constants::zNear, constants::zFar);
	glEnable(GL_DEPTH_TEST);
	cameraDirection = { 0, 0, -1 };
	cameraPosition = { 0, 0, 3 };
	cameraUp = { 0, 1, 0 };
	pitch = yaw = 0;
}

void RenderSystem::CalculateViewMatrix()
{
	//calculate our view model
	
	cameraRight = glm::normalize(glm::cross(cameraDirection, worldUp)); //find our right axis by taking world up and camera forward	
	cameraUp = glm::cross(cameraDirection, cameraRight); //calculate our camera up using our new right and forward (may be different than world up
	view = glm::lookAt(cameraPosition, cameraPosition + cameraDirection, worldUp);
}
void RenderSystem::CalculateModelMatrix(std::shared_ptr<MeshComponent> &ptr)
{
	model = glm::mat4(1.0f);
	//Translate
	model = glm::translate(model, mcptr->pos);
	////rotate on x, y, z may gimbal lock, might implement quaternions later if this becomes a problem
	model = glm::rotate(model, glm::radians(mcptr->rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(mcptr->rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(mcptr->rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void RenderSystem::Run(float deltaTime)
{
	//clear screen
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	entities = em->getEntitiesByComponent<MeshComponent>();
	for (unsigned int x = 0; x < entities.size(); ++x)
	{
		mcptr = entities[x]->getComp<MeshComponent>();
		mcptr->s.Use();
		
		CalculateModelMatrix(mcptr);
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

void RenderSystem::DoCameraMovement_FORDEBUG(glm::vec2 inputAxis, float deltaTime)
{
	cameraPosition += inputAxis.x * cameraRight * deltaTime;
	cameraDirectionFlat = { cameraDirection.x, 0, cameraDirection.z };
	cameraDirectionFlat = glm::normalize(cameraDirectionFlat);
	cameraPosition += inputAxis.y * cameraDirectionFlat * deltaTime;
}
void RenderSystem::DoCameraLook_FORDEBUG(glm::vec2 inputAxis, float deltaTime)
{
	yaw += inputAxis.x * deltaTime * constants::DebugVariables::GetInstance()->lrSensitivity;
	pitch += inputAxis.y * deltaTime * constants::DebugVariables::GetInstance()->udSensitivity;
	pitch = pitch > 89 ? 89 : pitch < -89 ? -89 : pitch; //clamp our pitch to max 89, otherwise our view will flip weirdly
	cameraDirection.y = sin(glm::radians(pitch));
	cameraDirection.z = -cos(glm::radians(yaw));
	cameraDirection.x = sin(glm::radians(yaw));
	glm::normalize(cameraDirection);
}
void RenderSystem::OverwriteCameraPosition_FORDEBUG(glm::vec3 newPosition)
{
	cameraPosition = newPosition;
}
void RenderSystem::OverwriteCameraDirection_FORDEBUG(glm::vec3 newRotation)
{
	cameraDirection = newRotation;
}