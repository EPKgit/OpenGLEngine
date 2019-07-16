#ifndef _PLAYERMOVEMENTSYSTEM_HPP
#define _PLAYERMOVEMENTSYSTEM_HPP

#include "System.hpp"

class PlayerMovementSystem : public System
{
public:
	void Run(float deltaTime);
};
#endif // !_PLAYERMOVEMENTSYSTEM_HPP
