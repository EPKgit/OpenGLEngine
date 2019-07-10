#ifndef _COMPONENTLOOKUP_HPP
#define _COMPONENTLOOKUP_HPP

#include <map>
#include <typeindex>
#include <typeinfo>

#include "Constants.hpp"

#include "MeshComponent.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"
#include "RigidbodyComponent.hpp"
#include "FollowComponent.hpp"
#include "SpringForceComponent.hpp"

class ComponentLookup
{
public:
	template <class T>
	static constants::ComponentType LookupComponent();

	static void SetupMap();
private:
	static std::map<std::type_index, constants::ComponentType> lookup;	
};

template <class T>
constants::ComponentType ComponentLookup::LookupComponent()
{
	auto i = lookup.find(typeid(T));
	if (i != lookup.end())
	{
		return (*i).second;
	}
	return constants::ComponentType::Base;
}


#endif // !_COMPONENTLOOKUP_HPP


