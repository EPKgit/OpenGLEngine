#include "TransformComponent.hpp"

TransformComponent::TransformComponent(std::weak_ptr<Entity> e, glm::vec3 p, glm::vec3 r, glm::vec3 s) 
	: Component(e), position(p), rotation(r), scale(s)
{
	type = constants::ComponentType::TransformComponent;
}