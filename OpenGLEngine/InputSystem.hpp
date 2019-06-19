#ifndef _INPUTSYSTEM_HPP
#define _INPUTSYSETM_HPP

#include "System.hpp"
#include "Graphics.hpp"
#include "Structs.hpp"
#include "RenderSystem.hpp"

class InputSystem : public System
{
public:
	void Run(float);
	//ONLY FOR DEBUG TESTING
	RenderSystem * rs;
private:
	/*structs::vec3d CheckAxis(sf::Keyboard::Key up, sf::Keyboard::Key left, sf::Keyboard::Key down, sf::Keyboard::Key right)
	{
		structs::vec3d temp = { 0, 0, 0 };
		if (sf::Keyboard::isKeyPressed(up))
		{
			temp.y += 1;
		}
		if (sf::Keyboard::isKeyPressed(down))
		{
			temp.y -= 1;
		}
		if (sf::Keyboard::isKeyPressed(left))
		{
			temp.x -= 1;
		}
		if (sf::Keyboard::isKeyPressed(right))
		{
			temp.x += 1;
		}
		return temp;
	}*/
};

#endif // ! _INPUTSYSTEM_HPP
