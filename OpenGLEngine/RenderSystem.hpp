#ifndef _RENDERSYSTEM_HPP
#define _RENDERSYSTEM_HPP

#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "System.hpp"
#include "Entity.hpp"
#include "MeshComponent.hpp"
#include "Graphics.hpp"
#include "Structs.hpp"
#include "EntityManager.hpp"
#include "Constants.hpp"

class RenderSystem : public System
{
private:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	std::shared_ptr<MeshComponent> mcptr;
public:
	RenderSystem();
	void Run(float);
};
#endif // !_RENDERSYSTEM_HPP
