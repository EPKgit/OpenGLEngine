#include "EntityManager.hpp"

#include "ComponentLookup.hpp"

EntityManager::EntityManager()
{
	numEntities = 0;
	ComponentLookup::SetupMap();
	singletonEntity = createEntity();
}

std::shared_ptr<Entity> EntityManager::createEntity()
{
	std::shared_ptr<Entity> e = std::make_shared<Entity>(numEntities++);
	entities.push_back(e);
	return e;
}

std::shared_ptr<Entity> EntityManager::addEntity(Entity e)
{
	std::shared_ptr<Entity> ep = std::make_shared<Entity>(e);
	e.ID = numEntities++;
	entities.push_back(ep);
	return ep;
}

bool EntityManager::deleteEntity(unsigned int i)
{
	for (unsigned int x = 0; x < entities.size(); ++x)
	{
		if (entities[x]->ID == i)
		{
			entities.erase(entities.begin() + x);
			return true;
		}
	}
	return false;
}

std::shared_ptr<Entity> EntityManager::getSingletonEntity()
{
	return singletonEntity;
}

