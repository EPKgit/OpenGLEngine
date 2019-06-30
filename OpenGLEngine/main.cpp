#include <iostream>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Constants.hpp"
#include "Library.hpp"
#include "Time.hpp"

#include "RenderSystemFPS.hpp"
#include "RenderSystemThirdPerson.hpp"
#include "InputSystem.hpp"
#include "FollowSystem.hpp"

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
	lib::CreateCubeEntity();
	lib::CreateCameraEntityThirdPerson();

	float deltaTime;
	RenderSystemThirdPerson rs;
	InputSystem is(&rs, window);
	Time * t = Time::GetInstance();
	char titleBuf[64];
	while (!glfwWindowShouldClose(window))
	{
		deltaTime = t->Tick();
		snprintf(titleBuf, 64, "OpenGLEngine FPS:%.2f", 1.0f / deltaTime);
		glfwSetWindowTitle(window, titleBuf);
		PROCESSINPUT_TEMP(window);

		is.Run(deltaTime);
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