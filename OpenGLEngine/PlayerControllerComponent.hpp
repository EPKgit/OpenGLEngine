#ifndef _PLAYERCONTROLLERCOMPONENT_HPP
#define _PLAYERCONTROLLERCOMPONENT_HPP

#include "Component.hpp"

class PlayerControllerComponent : public Component
{
public:
	PlayerControllerComponent(std::weak_ptr<Entity> e) : Component(e)
	{
		movementSpeed = 1;
		hSens = constants::defaultHorizSensitivity;
		vSens = constants::defaultVertSensitivity;
	}
	float movementSpeed;
	float hSens;
	float vSens;
};
#endif // !_PLAYERMOVEMENTCOMPONENT_HPP
