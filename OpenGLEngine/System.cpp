#include "System.hpp"

#include "EntityManager.hpp"

System::System()
{
	em = EntityManager::GetInstance();
}