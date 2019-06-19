#include "InputSystem.hpp"

//void InputSystem::Run(float deltaTime)
//{
//	structs::vec3d t;
//	t = CheckAxis(sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::S, sf::Keyboard::D);
//	if(t != 0.0f)
//		rs->DoCharacterMovement_FORDEBUG(t, deltaTime);
//	t = CheckAxis(sf::Keyboard::I, sf::Keyboard::J, sf::Keyboard::K, sf::Keyboard::L);
//	if(t != 0.0f)
//		rs->DoCharacterLook_FORDEBUG(t, deltaTime);
//	t = CheckAxis(sf::Keyboard::Up, sf::Keyboard::Left, sf::Keyboard::Down, sf::Keyboard::Right);
//	if(t != 0.0f)
//		rs->OffsetCameraPosition_FORDEBUG(t, deltaTime);
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
//	{
//		rs->OverwriteCameraPosition_FORDEBUG({ 0, 0, 0 });
//		rs->OverwriteCameraRotation_FORDEBUG({ 0, 0, 1 });
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
//	{
//		constants::DebugVariables::GetInstance()->wireframe = !constants::DebugVariables::GetInstance()->wireframe;
//	}
//}