#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "InputSystem.hpp"

#include "EntityManager.hpp"
#include "InputComponent.hpp"

InputSystem::InputSystem(GLFWwindow * _w) : window(_w)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, 0, 0);
	em->getSingletonEntity()->addComp<InputComponent>();
	keys =
	{
		{GLFW_KEY_W, InputMaps::W },
		{GLFW_KEY_A, InputMaps::A },
		{GLFW_KEY_S, InputMaps::S },
		{GLFW_KEY_D, InputMaps::D },
		{GLFW_KEY_SPACE, InputMaps::SPACE }
	};
}

void InputSystem::Run(float deltaTime)
{
	input = em->getSingletonEntity()->getComp<InputComponent>();
	//Check All Keys
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	for (auto k : keys)
	{
		CheckKey(k.first, k.second);
	}
	//Looking 
	CaptureMouseInput();

	//Moving
	CaptureMoveInput();

}

void InputSystem::CheckKey(int key, int keyIndex)
{
	int result = glfwGetKey(window, key);
	switch (result)
	{
	case GLFW_PRESS:
		input->downBits.set(keyIndex);
		input->heldBits.set(keyIndex);
		break;
	case GLFW_RELEASE:
		if (input->heldBits[keyIndex])
		{
			input->upBits.set(keyIndex);
			input->downBits.reset(keyIndex);
			input->heldBits.reset(keyIndex);
		}
		break;
	case GLFW_REPEAT:
		input->heldBits.set(keyIndex);
		break;
	default:
		break;
	}
}

void InputSystem::CaptureMouseInput()
{ //0/1 for fresh input, 2/3 for old input, 4/5 for diff
	glfwGetCursorPos(window, &input->mousePosition[0], &input->mousePosition[1]);
	double dX = input->mousePosition[0] - input->mousePosition[2];
	double dY = input->mousePosition[1] - input->mousePosition[3];
	if (dX != 0 || dY != 0)
	{
		input->mousePosition[2] = input->mousePosition[0];
		input->mousePosition[3] = input->mousePosition[1];
		input->mouseAxis.x = (float)dX;
		input->mouseAxis.y = -(float)dY;//mouse position is recorded from top to bottom so we need to reverse it
		input->mouseAxis = glm::normalize(input->mouseAxis);
	}
	else
	{
		input->mouseAxis = { 0, 0 };
	}
}

void InputSystem::CaptureMoveInput()
{
	input->moveAxis = { 0, 0 };
	input->moveAxis.y += input->heldBits[InputMaps::W];
	input->moveAxis.y -= input->heldBits[InputMaps::S];
	input->moveAxis.x += input->heldBits[InputMaps::D];
	input->moveAxis.x -= input->heldBits[InputMaps::A];
	if (input->moveAxis.x != 0 || input->moveAxis.y != 0)
	{
		input->moveAxis = glm::normalize(input->moveAxis);
	}
}
