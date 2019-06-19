#include "RenderSystem.hpp"

RenderSystem::RenderSystem()
{
	cameraPos = startingPosition;
	cameraDirection = startingDirection;
	orthoCameraDirection = { 1, 0, 0 };
	fYaw = 0;
	fPitch = 0;
}

//void RenderSystem::SetWindow(sf::RenderWindow * w)
//{
//	window = w;
//}

void RenderSystem::Run(float deltaTime)
{
	entities = em->getEntitiesByComponent<MeshComponent>();
	for (unsigned int x = 0; x < entities.size(); ++x)
	{
		//graphics::DrawMesh(*window, entities[x]->getComp<MeshComponent>()->m, cameraPos, cameraDirection);
	}
}

void RenderSystem::DoCharacterMovement_FORDEBUG(const structs::vec3d axis, float deltaTime)
{
	cameraPos += cameraDirection * -axis.y * deltaTime;
	cameraPos += orthoCameraDirection * -axis.x * deltaTime;
	if (constants::DebugVariables::GetInstance()->printCameraInfo)
	std::cout	<< "X:" << cameraDirection * axis.y << std::endl
				<< "Y:" << orthoCameraDirection * axis.x << std::endl
				<< cameraPos << std::endl;
}

void RenderSystem::DoCharacterLook_FORDEBUG(const structs::vec3d axis, float deltaTime)
{
	fYaw += axis.x * deltaTime;
	fPitch += -axis.y * deltaTime;
	graphics::ComputeXRotationMatrix(fPitch, rotX);
	graphics::ComputeYRotationMatrix(fYaw, rotY);
	graphics::MultiplyMatrixVector(rotX, startingDirection, cameraDirection);
	graphics::MultiplyMatrixVector(rotY, cameraDirection, cameraDirection);
	graphics::NormalizeVector(cameraDirection);
	graphics::CrossProduct(upDirection, cameraDirection, orthoCameraDirection);
	if (constants::DebugVariables::GetInstance()->printCameraInfo)
	std::cout	<< "NewCameraDir X:" << cameraDirection.x << std::endl
				<< "			 Y:" << cameraDirection.y << std::endl;
}

void RenderSystem::OffsetCameraPosition_FORDEBUG(structs::vec3d offset, float deltaTime)
{
	offset.x = -offset.x * constants::DebugVariables::GetInstance()->lrSensitivity;
	offset.y *= constants::DebugVariables::GetInstance()->udSensitivity;
	cameraPos += offset * deltaTime;
	std::cout << cameraPos << std::endl;
}

void RenderSystem::OverwriteCameraRotation_FORDEBUG(const structs::vec3d newAngle)
{
	cameraDirection = newAngle;
}

void RenderSystem::OverwriteCameraPosition_FORDEBUG(const structs::vec3d newPos)
{
	cameraPos = newPos;
}