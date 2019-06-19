#include "Entity.hpp"

std::shared_ptr<MeshComponent> Entity::addCompTest()
{
	if (hasComp<MeshComponent>())
	{
		return nullptr;
	}
	std::shared_ptr<Component> c(new MeshComponent());
	compBits.set(c->type);
	comps.push_back(c);

	return std::static_pointer_cast<MeshComponent>(c);
}