#ifndef _ENTITY_HPP
#define _ENTITY_HPP

#include <bitset>
#include <vector>
#include <memory>

#include "Library.hpp"
#include "Component.hpp"
#include "Constants.hpp"
#include "ComponentLookup.hpp"

class Entity
{
public:
	unsigned int ID;

	Entity(unsigned int i)
	{
		ID = i;
	}

	template<class T>
	bool hasComps();

	template<class T1, class T2, class ... rest>
	bool hasComps();

	template<class T>
	bool removeComp();

	template<class T>
	std::shared_ptr<T> addComp();

	template<class T, class ...Args>
	std::shared_ptr<T> addComp(Args ...args);

	template<class T>
	std::shared_ptr<T> addComp(std::shared_ptr<T>);

	template<class T>
	std::shared_ptr<T> getComp();

private:
	std::bitset<constants::maxComponents> compBits;
	std::vector<std::shared_ptr<Component>> comps;
};

template<class T>
bool Entity::hasComps()
{
	return compBits.test(ComponentLookup::LookupComponent<T>());
};

template<class T1, class T2, class... rest>
bool Entity::hasComps()
{
	if (compBits.test(ComponentLookup::LookupComponent<T1>()))
	{
		return hasComps<T2, rest ...>();
	}
	return false;
}

template<class T>
bool Entity::removeComp()
{
	constants::ComponentType c = ComponentLookup::LookupComponent<T>();
	for (unsigned int i; i < comps.size(); ++i)
	{
		if (comps[i]->type == c)
		{
			compBits.reset(c);
			comps.remove(i);
			return true;
		}
	}
	return false;
}

template<class T>
std::shared_ptr<T> Entity::addComp()
{
	if (hasComps<T>())
	{
		return nullptr;
	}
	std::shared_ptr<T> c = std::make_shared<T>();
	return addComp<T>(c);
}

template<class T, class ...Args>
std::shared_ptr<T> Entity::addComp(Args ...args)
{
	if (hasComps<T>())
	{
		return nullptr;
	}
	std::shared_ptr<T> c = std::make_shared<T>(args...);
	return addComp<T>(c);
}

template<class T>
std::shared_ptr<T> Entity::addComp(std::shared_ptr<T> c)
{
	if (hasComps<T>())
	{
		return nullptr;
	}
	compBits.set(c->type);
	comps.push_back(c);
	return c;
}

template<class T>
std::shared_ptr<T> Entity::getComp()
{
	constants::ComponentType c = ComponentLookup::LookupComponent<T>();
	if (hasComps<T>())
	{
		for (unsigned int i = 0; i < comps.size(); ++i)
		{
			if (comps[i]->type == c)
			{
				return std::static_pointer_cast<T>(comps[i]);
			}
		}
	}
	return nullptr;
}

#endif // !_ENTITY_HPP