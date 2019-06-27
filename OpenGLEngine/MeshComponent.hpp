#ifndef _MESHCOMPONENT_HPP
#define _MESHCOMPONENT_HPP

#include <vector>
#include <iterator>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Component.hpp"
#include "Structs.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

enum MeshType
{
	VertsOnly = 0, VertsPlusIndices
};

class MeshComponent : public Component
{
public:
	MeshType mType;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int numElements;
	glm::vec3 pos;
	glm::vec3 rot;
	std::vector<float> verts;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Shader s;
	MeshComponent();
	MeshComponent(	std::vector<float> *v, std::vector<unsigned int> *i, bool color = true, bool tex = true);
	MeshComponent(	std::vector<float> v, std::vector<unsigned int> i, bool color = true, bool tex = true) : 
					MeshComponent::MeshComponent(&v, &i, color, tex) { };
	MeshComponent(	std::vector<float> *v, bool color = true, bool tex = true);
	MeshComponent(	std::vector<float> v, bool color = true, bool tex = true) : 
					MeshComponent::MeshComponent(&v, color, tex) { };
	~MeshComponent();
};


#endif