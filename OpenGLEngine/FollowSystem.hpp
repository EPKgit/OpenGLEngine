#ifndef _FOLLOWSYSTEM_HPP
#define _FOLLOWSYSTEM_HPP

#include "System.hpp"

class TransformComponent;
class FollowComponent;

class FollowSystem : public System
{
public:
	void Run(float deltaTime);

private:
	std::shared_ptr<FollowComponent> fptr;
	std::shared_ptr<TransformComponent> tptr;
};
#endif