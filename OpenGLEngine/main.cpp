#include <iostream>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Constants.hpp"
#include "Library.hpp"
#include "Time.hpp"

//Systems
#include "RenderSystemFPS.hpp"
#include "RenderSystemThirdPerson.hpp"
#include "InputSystem.hpp"
#include "FollowSystem.hpp"
#include "RigidbodySystem.hpp"


//Temp includes for testing
#include "RigidbodyComponent.hpp"
#include "Entity.hpp"
#include "TransformComponent.hpp"

void window_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, constants::screenWidth, constants::screenHeight);
}

void GLFWstartup()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void PROCESSINPUT_TEMP(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void GameLoop(GLFWwindow * window)
{
	//std::shared_ptr<Entity> e = lib::CreateCameraEntityThirdPerson();
	std::shared_ptr<Entity> e = lib::CreateCameraEntityFPS();
	e->getComp<TransformComponent>()->position = { 0, 0, 2 };
	e = lib::CreateCubeEntity();
	std::shared_ptr<RigidbodyComponent> rb = e->addComp<RigidbodyComponent>();
	//rb->velocity.x = 1;
	rb->ApplyForce({ 0, 1, 0 }, 15, 1);
	rb->ApplyForce({ 1, 0, 0 }, 3, 1);


	float deltaTime;
	//RenderSystemThirdPerson rs;
	RenderSystemFPS rs;
	rs.Run(0);
	InputSystem is(&rs, window);
	RigidbodySystem  rbs;
	Time * t = Time::GetInstance();
	char titleBuf[64];
	while (!glfwWindowShouldClose(window))
	{
		deltaTime = t->Tick();
		snprintf(titleBuf, 64, "OpenGLEngine FPS:%.2f", 1.0f / deltaTime);
		glfwSetWindowTitle(window, titleBuf);
		PROCESSINPUT_TEMP(window);

		is.Run(deltaTime);
		rbs.Run(deltaTime);
		rs.Run(deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
}

int main()
{
	GLFWstartup();
	GLFWwindow * window = glfwCreateWindow(constants::screenWidth, constants::screenHeight, "Testing", nullptr, nullptr);
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
	glViewport(0, 0, constants::screenWidth, constants::screenHeight);
	glfwSetFramebufferSizeCallback(window, window_resize_callback);

	GameLoop(window);
	glfwTerminate();
	return 0;
}