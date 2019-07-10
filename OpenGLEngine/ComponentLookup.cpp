#include "ComponentLookup.hpp"

std::map<std::type_index, constants::ComponentType> ComponentLookup::lookup;

void ComponentLookup::SetupMap()
{
	ComponentLookup::lookup[typeid(MeshComponent)] = constants::ComponentType::MeshComponent;
	ComponentLookup::lookup[typeid(TransformComponent)] = constants::ComponentType::TransformComponent;
	ComponentLookup::lookup[typeid(CameraComponent)] = constants::ComponentType::CameraComponent;
	ComponentLookup::lookup[typeid(RigidbodyComponent)] = constants::ComponentType::RigidbodyComponent;
	ComponentLookup::lookup[typeid(FollowComponent)] = constants::ComponentType::FollowComponent;
	ComponentLookup::lookup[typeid(SpringForceComponent)] = constants::ComponentType::SpringForceComponent;
}