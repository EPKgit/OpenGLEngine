#ifndef _CAMERACOMPONENT_HPP
#define _CAMERACOMPONENT_HPP

#include <glm/glm.hpp>

#include "Component.hpp"

class CameraComponent : public Component
{
public:
	CameraComponent(glm::vec3 cp = { 0, 0, 0 }, glm::vec3 cd = { 0, 0, -1 }) : cameraOffset(cp), cameraDirection(cd) 
	{
		type = constants::ComponentType::CameraComponent;
		Init(cp, cd);
	}
	void Init(glm::vec3 cp, glm::vec3 cd)
	{
		cameraDistance = glm::length(cp);
		yaw = 0;
		if (cp.y != 0)
		{
			pitch = atanf(cp.z / cp.y);
		}
	}
	glm::vec3 cameraOffset;
	glm::vec3 cameraDirection;
	float pitch;
	float yaw;
	float cameraDistance;
};
#endif // !_CAMERACOMPONENT_HPP
