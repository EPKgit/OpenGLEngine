#ifndef _CONSTANTS_HPP
#define _CONSTANTS_HPP

#include "glm/glm.hpp"

#include "Library.hpp"
#include "Singleton.hpp"

namespace constants
{
	enum ComponentType
	{
		Base = 0, MeshComponent = 1, TransformComponent = 2, CameraComponent = 3, RigidbodyComponent = 4, FollowComponent = 69
	};

	const int maxComponents = 128;

	const unsigned int screenHeight = 768;
	const unsigned int screenWidth = 1024;
	const float fieldOfView = 90.0f;
	const float zNear = 0.1f;
	const float zFar = 100.0f;
	const float aspectRatio = (float)screenWidth / screenHeight;

	const float fixedTimeStep = 0.01f;
	const glm::vec3 gravity = { 0, -10.0f, 0 };
	
	class DebugVariables : public Singleton<DebugVariables>
	{
	public:
		bool wireframe = false;
		bool printCameraInfo = false;
		float udSensitivity = 75.0f;
		float lrSensitivity = 75.0f;
	};
};

#endif // !_CONSTANTS_HPP
