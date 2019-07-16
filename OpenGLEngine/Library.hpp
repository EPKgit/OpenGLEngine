#ifndef _LIB_HPP
#define _LIB_HPP

#include <memory>

class Entity;

namespace lib
{
	inline float DegToRadf(float degreeMeasure);
	inline float RadToDegf(float radMeasure);
	std::shared_ptr<Entity> CreateCubeEntity();
	std::shared_ptr<Entity> CreateCameraEntityFPS();
	std::shared_ptr<Entity> CreateCameraEntityThirdPerson();
	std::shared_ptr<Entity> CreatePlayerEntity();
};


#endif // ! _LIB_HPP
