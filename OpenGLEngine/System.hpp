#ifndef _SYSTEM_HPP
#define _SYSTEM_HPP

#include <memory>
#include <vector>

class Entity;
class EntityManager;

class System
{
protected:
	std::vector<std::shared_ptr<Entity>> entities;
public:
	System();
	EntityManager * em;
	virtual void Run(float) = 0;
};

#endif // !_SYSTEM_HPP
