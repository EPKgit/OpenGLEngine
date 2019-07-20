#ifndef _PLAYERMOVEMENTSYSTEM_HPP
#define _PLAYERMOVEMENTSYSTEM_HPP

#include "System.hpp"

class InputComponent;
class TransformComponent;
class CameraComponent;
class PlayerControllerComponent;

class PlayerControllerSystem : public System
{
public:
	void Run(float deltaTime);

private:
	void CameraLookFPS(float deltaTime, std::shared_ptr<InputComponent> iptr, std::shared_ptr<TransformComponent> tptr, std::shared_ptr<CameraComponent> cptr, std::shared_ptr<PlayerControllerComponent> pcptr);
	void CameraLookTPS(float deltaTime, std::shared_ptr<InputComponent> iptr, std::shared_ptr<TransformComponent> tptr, std::shared_ptr<CameraComponent> cptr, std::shared_ptr<PlayerControllerComponent> pcptr);
};
#endif // !_PLAYERMOVEMENTSYSTEM_HPP
