#ifndef _SYSTEM_HPP
#define _SYSTEM_HPP

#include <memory>

#include "EntityManager.hpp"

class System
{
protected:
	std::vector<std::shared_ptr<Entity>> entities;
public:
	System()
	{
		em = EntityManager::GetInstance();
	}
	EntityManager * em;
	virtual void Run(float) = 0;
};

#endif // !_SYSTEM_HPP
