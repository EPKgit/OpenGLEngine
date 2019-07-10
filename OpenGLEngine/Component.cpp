#include "Component.hpp"

Component::Component(std::weak_ptr<Entity> e) : entity(e)
{
	type = constants::ComponentType::Base;
}
Component::~Component() { }