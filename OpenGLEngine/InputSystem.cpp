#include "InputSystem.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "RenderSystemFPS.hpp"
#include "RenderSystemThirdPerson.hpp"

InputSystem::InputSystem(RenderSystemFPS * _rs, GLFWwindow * _w) : rs(_rs), window(_w)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, 0, 0);
	FPS = true;
}


InputSystem::InputSystem(RenderSystemThirdPerson * _rs, GLFWwindow * _w) : rs2(_rs), window(_w)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, 0, 0);
	FPS = false;
}

void InputSystem::Run(float deltaTime)
{
	//Looking
	CaptureMouseInput(deltaTime);

	//Moving
	CheckAxis(GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, inputAxis);
	if (inputAxis.x != 0 || inputAxis.y != 0)
	{
		if (FPS)
		{
			rs->DoCameraMovement_FORDEBUG(inputAxis, deltaTime);
		}
		else
		{
			rs2->DoCameraMovement_FORDEBUG(inputAxis, deltaTime);
		}
	}
}

void InputSystem::CaptureMouseInput(float deltaTime)
{ //0/1 for fresh input, 2/3 for old input, 4/5 for diff
	glfwGetCursorPos(window, &mousePosition[0], &mousePosition[1]);
	mousePosition[4] = mousePosition[0] - mousePosition[2];//new minus old
	mousePosition[5] = mousePosition[1] - mousePosition[3];
	if (mousePosition[4] != 0 || mousePosition[5] != 0)
	{
		mousePosition[2] = mousePosition[0];
		mousePosition[3] = mousePosition[1];
		inputAxis.x = (float)(mousePosition[4]);
		inputAxis.y = -(float)(mousePosition[5]);//mouse position is recorded from top to bottom so we need to reverse it
	}
	else
	{
		inputAxis = { 0, 0 };
	}
	if (FPS)
	{
		rs->DoCameraLook_FORDEBUG(inputAxis, deltaTime);
	}
	else
	{
		rs2->DoCameraLook_FORDEBUG(inputAxis, deltaTime);
	}
}

void InputSystem::CheckAxis(int up, int left, int down, int right, glm::vec2 &o)
{
	o = { 0, 0 };
	if (glfwGetKey(window, up) == GLFW_PRESS)
	{
		o.y += 1;
	}
	if (glfwGetKey(window, down) == GLFW_PRESS)
	{
		o.y -= 1;
	}
	if (glfwGetKey(window, left) == GLFW_PRESS)
	{
		o.x -= 1;
	}
	if (glfwGetKey(window, right) == GLFW_PRESS)
	{
		o.x += 1;
	}
}