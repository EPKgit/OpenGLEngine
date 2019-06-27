#ifndef _ENTITY_HPP
#define _ENTITY_HPP

#include <bitset>
#include <typeinfo>
#include <vector>
#include <memory>

#include "MeshComponent.hpp"
#include "Constants.hpp"
#include "Component.hpp"

class Entity
{
public:
	unsigned int ID;

	Entity(unsigned int i)
	{
		ID = i;
	}

	template<class T>
	bool hasComp();

	template<class T1, class ... others>
	bool hasComps();

	template<class T>
	bool removeComp();

	template<class T>
	std::shared_ptr<T> addComp();

	template<class T>
	std::shared_ptr<T> addComp(std::shared_ptr<T>);

	template<class T>
	std::shared_ptr<T> getComp();

private:
	std::bitset<constants::maxComponents> compBits;
	std::vector<std::shared_ptr<Component>> comps;

};

template<class T>
bool Entity::hasComp()
{
	T c;
	return compBits.test(c.type);
};

template<class T1, class ... others>
bool Entity::hasComps()
{
	T1 c;
	return compBits.test(c.type) && hasComps<others ...>();
}

template<class T>
bool Entity::removeComp()
{
	T c;
	for (unsigned int i; i < comps.size(); ++i)
	{
		if (comps[i]->type == c.type)
		{
			compBits.reset(c.type);
			comps.remove(i);
			return true;
		}
	}
	return false;
}

template<class T>
std::shared_ptr<T> Entity::addComp()
{
	if (hasComp<T>())
	{
		return nullptr;
	}
	std::shared_ptr<T> c = std::make_shared<T>();
	return addComp<T>(c);
}

template<class T>
std::shared_ptr<T> Entity::addComp(std::shared_ptr<T> c)
{
	if (hasComp<T>())
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
	T c;
	if (hasComp<T>())
	{
		for (unsigned int i = 0; i < comps.size(); ++i)
		{
			if (comps[i]->type == c.type)
			{
				return std::static_pointer_cast<T>(comps[i]);
			}
		}
	}
	return nullptr;
}

#endif // !_ENTITY_HPP