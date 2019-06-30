#include "TransformComponent.hpp"

TransformComponent::TransformComponent(glm::vec3 p, glm::vec3 r, glm::vec3 s) : position(p), rotation(r), scale(s)
{
	type = constants::ComponentType::TransformComponent;
}