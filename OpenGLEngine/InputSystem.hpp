#ifndef _INPUTSYSTEM_HPP
#define _INPUTSYSTEM_HPP

#include <vector>
#include <utility>

#include "System.hpp"

class InputComponent;
struct GLFWwindow;

class InputSystem : public System
{
public:
	InputSystem(GLFWwindow * _w);
	void Run(float);
	//ONLY FOR DEBUG TESTING
private:
	GLFWwindow * window;
	std::shared_ptr<InputComponent> input;
	std::vector<std::pair<int, int>> keys;
	void CheckKey(int key, int keyIndex);
	void CaptureMouseInput();
	void CaptureMoveInput();
};

#endif // ! _INPUTSYSTEM_HPP
