#ifndef _RENDERSYSTEMTHIRDPERSON_HPP
#define _RENDERSYSTEMTHIRDPERSON_HPP

#include <memory>

#include <glm/glm.hpp>

#include "System.hpp"

class MeshComponent;
class TransformComponent;
class CameraComponent;

class RenderSystemThirdPerson : public System
{
public:
	RenderSystemThirdPerson();
	void Run(float);
private:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	glm::vec3 cameraDirectionFlat;
	const glm::vec3 worldUp = { 0, 1, 0 };
	std::shared_ptr<MeshComponent> mcptr;
	std::shared_ptr<TransformComponent> mtptr;

	std::shared_ptr<CameraComponent> cptr;
	std::shared_ptr<TransformComponent> ctptr;
	void CalculateViewMatrix();
	void CalculateModelMatrix(); 
	void DoCameraMovement(glm::vec2 inputAxis, float deltaTime);
	void DoCameraLook(glm::vec2 inputAxis, float deltaTime);
};
#endif // !_RENDERSYSTEM_HPP
