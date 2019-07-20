#ifndef _RENDERSYSTEM_HPP
#define _RENDERSYSTEM_HPP

#include <memory>

#include <glm/glm.hpp>

#include "System.hpp"

class MeshComponent;
class TransformComponent;
class CameraComponent;

class RenderSystem : public System
{
public:
	RenderSystem();
	void Run(float);
	/*
	void OverwriteCameraPosition_FORDEBUG(glm::vec3 newPosition);
	void OverwriteCameraDirection_FORDEBUG(glm::vec3 newRotation);*/
private:
	const glm::vec3 worldUp = { 0, 1, 0 };
	std::shared_ptr<MeshComponent> mcptr;
	std::shared_ptr<TransformComponent> mtptr;

	std::shared_ptr<CameraComponent> cptr;
	std::shared_ptr<TransformComponent> ctptr;
	void CalculateViewMatrix();
	void CalculateModelMatrix();
};
#endif // !_RENDERSYSTEM_HPP
