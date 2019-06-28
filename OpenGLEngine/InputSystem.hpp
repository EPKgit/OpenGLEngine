#ifndef _INPUTSYSTEM_HPP
#define _INPUTSYSTEM_HPP

#include "glm/glm.hpp"

#include "System.hpp"

class RenderSystem;
struct GLFWwindow;

class InputSystem : public System
{
public:
	InputSystem(RenderSystem * _rs, GLFWwindow * _w);
	
	void Run(float);
	//ONLY FOR DEBUG TESTING
private:
	GLFWwindow * window;
	RenderSystem * rs;
	glm::vec2 inputAxis;
	double mousePosition[6];//0/1 for fresh input, 2/3 for old input, 4/5 for diff
	void CaptureMouseInput(float);
	void CheckAxis(int up, int left, int down, int right, glm::vec2 &o);
};

#endif // ! _INPUTSYSTEM_HPP
