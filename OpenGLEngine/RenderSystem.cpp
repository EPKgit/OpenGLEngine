#include "RenderSystem.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "MeshComponent.hpp"
#include "EntityManager.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"

RenderSystem::RenderSystem()
{
	glEnable(GL_DEPTH_TEST);
	Run(0);
}

void RenderSystem::CalculateViewMatrix()
{
	//calculate our view model
	cptr->cameraRight = glm::normalize(glm::cross(cptr->cameraDirection, worldUp)); //find our right axis by taking world up and camera forward	
	cptr->cameraUp = glm::cross(cptr->cameraDirection, cptr->cameraRight); //calculate our camera up using our new right and forward (may be different than world up
	cptr->view = glm::lookAt(cptr->cameraOffset + ctptr->position, cptr->cameraOffset + ctptr->position + cptr->cameraDirection, worldUp);
}
void RenderSystem::CalculateModelMatrix()
{
	mcptr->model = glm::mat4(1.0f);
	//We apply transformation in reverse order, as they will be reversed in the resulting matrix
	//Translate
	mcptr->model = glm::translate(mcptr->model, mtptr->position);
	////rotate on x, y, z may gimbal lock, might implement quaternions later if this becomes a problem
	mcptr->model = glm::rotate(mcptr->model, glm::radians(mtptr->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	mcptr->model = glm::rotate(mcptr->model, glm::radians(mtptr->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	mcptr->model = glm::rotate(mcptr->model, glm::radians(mtptr->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	//Scale
	mcptr->model = glm::scale(mcptr->model, mtptr->scale);
}

void RenderSystem::Run(float deltaTime)
{
	//clear screen
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::vector<std::shared_ptr<Entity>> cams = em->getEntitiesByComponents<CameraComponent, TransformComponent>();
	entities = em->getEntitiesByComponents<MeshComponent, TransformComponent>();
	for (unsigned int x = 0; x < cams.size(); ++x)
	{
		cptr = cams[x]->getComp<CameraComponent>();
		if (cptr->dirty)
		{
			ctptr = cams[x]->getComp<TransformComponent>();
			cptr->dirty = false;
			//std::cout << "recomputing view matrix\n";
			CalculateViewMatrix(); //pre generate all of our view matricies but only if the direction has changed since last time
		}
	}
	for (unsigned int x = 0; x < entities.size(); ++x)
	{
		mcptr = entities[x]->getComp<MeshComponent>();
		mtptr = entities[x]->getComp<TransformComponent>();
		
		CalculateModelMatrix();

		mcptr->s.Use();
		mcptr->s.setMat4("model", mcptr->model);
		mcptr->s.setMat4("projection", constants::CameraVariables::GetInstance()->projection);
		
		for(unsigned int y = 0; y < cams.size(); ++y) //draw our model on each of our cameras
		{
			cptr = cams[y]->getComp<CameraComponent>();
			//attach out matrices to our shader
			
			mcptr->s.setMat4("view", cptr->view);
			

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