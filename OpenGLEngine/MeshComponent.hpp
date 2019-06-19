#ifndef _MESHCOMPONENT_HPP
#define _MESHCOMPONENT_HPP

#include "Component.hpp"
#include "Structs.hpp"


class MeshComponent : public Component
{
public:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	structs::vec3d pos;
	structs::vec3d rot;
	MeshComponent();
};


#endif