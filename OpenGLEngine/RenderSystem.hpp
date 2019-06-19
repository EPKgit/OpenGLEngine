#ifndef _RENDERSYSTEM_HPP
#define _RENDERSYSTEM_HPP

#include <vector>
#include <iostream>

#include "System.hpp"
#include "Entity.hpp"
#include "MeshComponent.hpp"
#include "Graphics.hpp"
#include "Structs.hpp"
#include "EntityManager.hpp"
#include "Constants.hpp"

class RenderSystem : public System
{
private:
	/*sf::RenderWindow * window;*/
	const structs::vec3d startingPosition = { 0, 1.5, 0 };
	const structs::vec3d startingDirection = { 0, 0, 1 };
	const structs::vec3d upDirection = { 0, 1 ,0 };
	structs::vec3d cameraPos;
	structs::vec3d cameraDirection;
	structs::vec3d orthoCameraDirection;
	structs::mat4x4 rotX;
	structs::mat4x4 rotY;
	float fYaw;
	float fPitch;
public:
	RenderSystem();
	/*void SetWindow(sf::RenderWindow *);*/
	void Run(float);
	void DoCharacterMovement_FORDEBUG(const structs::vec3d, float);
	void DoCharacterLook_FORDEBUG(const structs::vec3d, float);
	void OffsetCameraPosition_FORDEBUG(const structs::vec3d, float);
	void OffsetCameraRotation_FORDEBUG(const structs::vec3d, float);
	void OverwriteCameraRotation_FORDEBUG(const structs::vec3d newAngle);
	void OverwriteCameraPosition_FORDEBUG(const structs::vec3d newPos);
};
#endif // !_RENDERSYSTEM_HPP
