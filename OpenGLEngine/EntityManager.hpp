#ifndef _ENTITY_MANAGER_HPP
#define _ENTITY_MANAGER_HPP

#include <vector>
#include <memory>

#include "Entity.hpp"
#include "Singleton.hpp"

class EntityManager : public Singleton<EntityManager>
{
private:
	friend class Singleton<EntityManager>;
	EntityManager();
	std::vector<std::shared_ptr<Entity>> entities;
	unsigned int numEntities;
public:
	
	std::shared_ptr<Entity> createEntity();
	std::shared_ptr<Entity> addEntity(Entity e);
	bool deleteEntity(unsigned int i);

	template<class T>
	std::vector<std::shared_ptr<Entity>> getEntitiesByComponent();

	template<class T, class ... rest>
	std::vector<std::shared_ptr<Entity>> getEntitiesByComponents();

};

template<class T>
std::vector<std::shared_ptr<Entity>> EntityManager::getEntitiesByComponent()
{
	std::vector<std::shared_ptr<Entity>> temp;
	for (unsigned int x = 0; x < entities.size(); ++x)
	{
		if (entities[x]->hasComps<T>())
		{
			temp.push_back(entities[x]);
		}
	}
	return temp;
}

template<class T, class ... rest>
std::vector<std::shared_ptr<Entity>> EntityManager::getEntitiesByComponents()
{
	std::vector<std::shared_ptr<Entity>> temp;
	for (unsigned int x = 0; x < entities.size(); ++x)
	{
		if (entities[x]->hasComps<T, rest ...>())
		{
			temp.push_back(entities[x]);
		}
	}
	return temp;
}

#endif // !_ENTITY_MANAGER
