#ifndef _CONSTANTS_HPP
#define _CONSTANTS_HPP

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "Singleton.hpp"

namespace constants
{
	enum ComponentType
	{
		Base = 0, 
		MeshComponent, 
		TransformComponent, 
		CameraComponent, 
		RigidbodyComponent, 
		SpringForceComponent,
		InputComponent,
		FollowComponent,
		PlayerMovement,
		NetworkComponent,
		
		COUNT
	};

	const int maxComponents = ComponentType::COUNT;

	class CameraVariables : public Singleton<CameraVariables>
	{
	public:
		CameraVariables() : Singleton()
		{
			projection = glm::perspective(glm::radians(fieldOfView), aspectRatio, zNear, zFar);
		}
		unsigned int screenHeight = (int)(768 * 0.5);
		unsigned int screenWidth = (int)(1024 * 0.5);
		float fieldOfView = 90.0f;
		float zNear = 0.1f;
		float zFar = 100.0f;
		float aspectRatio = (float)screenWidth / screenHeight;
		glm::mat4 projection;
	};

	const int numberOfFixedStepsPerSecond = 50;
	const float fixedTimeStep = 1.0f / numberOfFixedStepsPerSecond;
	const glm::vec3 gravity = { 0, -10.0f, 0 };

	const char* const defaultPort = "25408";
	const char* const defaultHostName = "127.0.0.1";
	const int timeToWaitForConnection = 2.0f;
	const int networkTicksPerSecond = 10;
	const float timePerNetworkTick = 1.0f / networkTicksPerSecond;

	const float defaultVertSensitivity = 250.0f;
	const float defaultHorizSensitivity = 250.0f;
	
	class DebugVariables : public Singleton<DebugVariables>
	{
	public:
		bool wireframe = false;
		bool printCameraInfo = false;
	};
};

#endif // !_CONSTANTS_HPP
