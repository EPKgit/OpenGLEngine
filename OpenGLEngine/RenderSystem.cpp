#include "RenderSystem.hpp"

RenderSystem::RenderSystem()
{
	projection = glm::perspective(glm::radians(constants::fieldOfView), constants::aspectRatio, constants::zNear, constants::zFar);
	glEnable(GL_DEPTH_TEST);
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
		model = glm::mat4(1.0f);
		//Translate
		model = glm::translate(model, mcptr->pos);
		////rotate on x, y, z may gimbal lock, might implement quaternions later if this becomes a problem
		model = glm::rotate(model, glm::radians(mcptr->rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mcptr->rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mcptr->rot.z), glm::vec3(0.0f, 0.0f, 1.0f));

		//calculate our view model
		view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		//attach out matrices to our shader
		mcptr->s.setMat4("model", model);
		mcptr->s.setMat4("view", view);
		mcptr->s.setMat4("projection", projection);
		
		for (int x = 0; x < mcptr->textures.size(); ++x)
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