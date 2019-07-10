#ifndef _ENTITY_HPP
#define _ENTITY_HPP

#include <bitset>
#include <vector>
#include <memory>

#include "Library.hpp"
#include "Component.hpp"
#include "Constants.hpp"
#include "ComponentLookup.hpp"

class Entity : public std::enable_shared_from_this<Entity>
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
	for (auto x = comps.begin(); x != comps.end(); ++x)
	{
		if ((*x)->type == c)
		{
			compBits.reset(c);
			comps.erase(x);
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
	std::weak_ptr<Entity> e = weak_from_this();
	std::shared_ptr<Entity> e2 = shared_from_this();
	std::shared_ptr<T> c = std::make_shared<T>(this->weak_from_this());
	return addComp<T>(c);
}

template<class T, class ...Args>
std::shared_ptr<T> Entity::addComp(Args ...args)
{
	if (hasComps<T>())
	{
		return nullptr;
	}
	std::shared_ptr<T> c = std::make_shared<T>(this->weak_from_this(), args...);
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
	std::shared_ptr<Component> cptr = std::static_pointer_cast<Component>(c);
	cptr->entity = weak_from_this();
	return c;
}

template<class T>
std::shared_ptr<T> Entity::getComp()
{
	constants::ComponentType c = ComponentLookup::LookupComponent<T>();
	if (hasComps<T>())
	{
		for (unsigned int x = 0; x < comps.size(); ++x)
		{
			if (comps[x]->type == c)
			{
				return std::static_pointer_cast<T>(comps[x]);
			}
		}
	}
	return nullptr;
}

#endif // !_ENTITY_HPP