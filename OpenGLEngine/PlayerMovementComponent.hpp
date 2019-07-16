#ifndef _PLAYERMOVEMENTCOMPONENT_HPP
#define _PLAYERMOVEMENTCOMPONENT_HPP

#include "Component.hpp"

class PlayerMovementComponent : public Component
{
public:
	PlayerMovementComponent(std::weak_ptr<Entity> e) : Component(e)
	{
		movementSpeed = 1;
	}
	float movementSpeed;
};
#endif // !_PLAYERMOVEMENTCOMPONENT_HPP
