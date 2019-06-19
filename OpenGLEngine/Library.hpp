#ifndef _LIB_HPP
#define _LIB_HPP

#define _USE_MATH_DEFINES

#include <math.h>

#include "Structs.hpp"

namespace lib
{
	inline float DegToRadf(float degreeMeasure)
	{
		return degreeMeasure * (float)M_PI / 180.0f;
	}
	inline float RadToDeg(float radMeasure)
	{
		return radMeasure / (float)M_PI * 180.0f;
	}

	void CreateCubeMesh(structs::mesh &);
};


#endif // ! _LIB_HPP
