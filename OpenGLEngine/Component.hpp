#ifndef _COMPONENT_HPP
#define _COMPONENT_HPP

#include "Constants.hpp"

class Component
{
public:
	Component();
	virtual ~Component();
	constants::ComponentType type;
};
#endif // ! _COMPONENT_HPP
