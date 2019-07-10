#ifndef _COMPONENT_HPP
#define _COMPONENT_HPP

#include <memory>

#include "Constants.hpp"

class Entity;

class Component
{
public:
	Component(std::weak_ptr<Entity> e);
	virtual ~Component();
	constants::ComponentType type;
	std::weak_ptr<Entity> entity;
};
#endif // ! _COMPONENT_HPP
