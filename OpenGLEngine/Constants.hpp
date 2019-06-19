#ifndef _CONSTANTS_HPP
#define _CONSTANTS_HPP

#include "Library.hpp"
#include "Structs.hpp"
#include "Singleton.hpp"

namespace constants
{
	enum ComponentType
	{
		Base = 0, MeshComponent = 1
	};

	const int maxComponents = 128;

	const unsigned int screenHeight = 768;
	const unsigned int screenWidth = 1024;
	const float fieldOfView = 90.0f;
	const float zNear = 0.1f;
	const float zFar = 100.0f;
	const float fovScaling = 1.0f / tanf(lib::DegToRadf(fieldOfView) * 0.5f);
	const float aspectRatio = (float)screenHeight / screenWidth;

	namespace matrices
	{
		const structs::mat4x4 projectionMatrix =
		{
			{
				{ aspectRatio * fovScaling, 0, 0, 0 },
				{ 0, fovScaling, 0, 0 },
				{ 0, 0, zFar / (zFar - zNear), 1 },
				{ 0, 0, (-zFar * zNear) / (zFar - zNear), 0 }
			}
		};
	};
	
	class DebugVariables : public Singleton<DebugVariables>
	{
	public:
		bool wireframe = false;
		bool printCameraInfo = false;
		float udSensitivity = 1.0f;
		float lrSensitivity = 1.0f;
	};

};

#endif // !_CONSTANTS_HPP
