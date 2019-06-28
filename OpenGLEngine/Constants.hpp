#ifndef _CONSTANTS_HPP
#define _CONSTANTS_HPP

#include "Library.hpp"
#include "Singleton.hpp"

namespace constants
{
	enum ComponentType
	{
		Base = 0, MeshComponent = 1, PositionComponent = 2, FollowComponent = 69
	};

	const int maxComponents = 128;

	const unsigned int screenHeight = 768;
	const unsigned int screenWidth = 1024;
	const float fieldOfView = 90.0f;
	const float zNear = 0.1f;
	const float zFar = 100.0f;
	const float aspectRatio = (float)screenWidth / screenHeight ;
	
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
