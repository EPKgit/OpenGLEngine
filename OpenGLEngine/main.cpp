#include <iostream>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Constants.hpp"
#include "Library.hpp"
#include "Time.hpp"

//Systems
#include "RenderSystem.hpp"
#include "InputSystem.hpp"
#include "FollowSystem.hpp"
#include "RigidbodySystem.hpp"
#include "PlayerControllerSystem.hpp"


//Temp includes for testing
#include "RigidbodyComponent.hpp"
#include "Entity.hpp"
#include "TransformComponent.hpp"
#include "SpringForceComponent.hpp"

void window_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, constants::CameraVariables::GetInstance()->screenWidth, constants::CameraVariables::GetInstance()->screenHeight);
}

void GLFWstartup()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GameLoop(GLFWwindow * window)
{
	//std::shared_ptr<Entity> e = lib::CreateCameraEntityThirdPerson();
	std::shared_ptr<Entity> e = lib::CreatePlayerEntity();
	e->getComp<TransformComponent>()->position = { 0, 0, 2 };

	//e = lib::CreateCubeEntity();
	//e->getComp<TransformComponent>()->scale.z = 100;
	//e->getComp<TransformComponent>()->scale.x = 100;
	//e->getComp<TransformComponent>()->scale.y = 0.5;
	//e->getComp<TransformComponent>()->position.y = -1;
	//e->getComp<MeshComponent>()->textures.clear();
	//std::shared_ptr<RigidbodyComponent> rb = e->addComp<RigidbodyComponent>();
	//rb->SetInfiniteMass();

	e = lib::CreateCubeEntity();
	e->addComp<RigidbodyComponent>();
	e->addComp<SpringForceComponent, glm::vec3, float, float>({ 0, 3, 0 }, 10.0f, 1.0f);
	std::shared_ptr<TransformComponent> tptr = e->getComp<TransformComponent>();
	tptr->position = { 0, 0, 0 };

	/*e = lib::CreateCubeEntity();
	e->addComp<RigidbodyComponent>();
	e->getComp<TransformComponent>()->position = { 3, 0, 0 };
	e->addComp<SpringForceComponent, std::shared_ptr<TransformComponent>, float, float>(tptr, 10.0f, 3.0f);*/


	float deltaTime;
	std::vector<System *> systems;
	RenderSystem rs;
	InputSystem is(window);
	PlayerControllerSystem pms;
	RigidbodySystem rbs;
	systems.push_back(&rs);
	systems.push_back(&is);
	systems.push_back(&pms);
	systems.push_back(&rbs);

	Time * t = Time::GetInstance();
	char titleBuf[64];
	while (!glfwWindowShouldClose(window))
	{
		deltaTime = t->Tick();
		snprintf(titleBuf, 64, "OpenGLEngine FPS:%.2f", 1.0f / deltaTime);
		glfwSetWindowTitle(window, titleBuf);

		for (auto x : systems)
		{
			x->Run(deltaTime);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
}

int main()
{
	GLFWstartup();
	GLFWwindow * window = glfwCreateWindow(constants::CameraVariables::GetInstance()->screenWidth, constants::CameraVariables::GetInstance()->screenHeight, "Testing", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, constants::CameraVariables::GetInstance()->screenWidth, constants::CameraVariables::GetInstance()->screenHeight);
	glfwSetFramebufferSizeCallback(window, window_resize_callback);

	GameLoop(window);
	glfwTerminate();
	return 0;
}