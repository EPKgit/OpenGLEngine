#ifndef _PHYSICSSUBSYSTEMS_HPP
#define _PHYSICSSUBSYSTEMS_HPP

#include <vector>
#include <memory>

class Entity;

class PhysicsSubsystems
{
public:
	void Run(float deltaTime, std::vector<std::shared_ptr<Entity>> &entities);
private:
	void PerformSpringCalculation(std::vector<std::shared_ptr<Entity>> &entities);
};
#endif // !_PHYSICSSUBSYSTEMS_HPP
