#ifndef _COMPONENT_HPP
#define _COMPONENT_HPP

#include "Constants.hpp"

class Component
{
private:

public:
	Component();
	virtual ~Component();
	constants::ComponentType type = constants::ComponentType::Base;
};
#endif // ! _COMPONENT_HPP
