#ifndef _MESHCOMPONENT_HPP
#define _MESHCOMPONENT_HPP

#include <vector>
#include <iterator>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Component.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

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
	std::vector<float> verts;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Shader s;
	glm::mat4 model;
	MeshComponent(	std::weak_ptr<Entity> e);
	MeshComponent(	std::weak_ptr<Entity> e, std::vector<float> *v, std::vector<unsigned int> *i, bool color = true, bool tex = true);
	MeshComponent(	std::weak_ptr<Entity> e, std::vector<float> v, std::vector<unsigned int> i, bool color = true, bool tex = true) :
					MeshComponent::MeshComponent(e, &v, &i, color, tex) { };
	MeshComponent(	std::weak_ptr<Entity> e, std::vector<float> *v, bool color = true, bool tex = true);
	MeshComponent(	std::weak_ptr<Entity> e, std::vector<float> v, bool color = true, bool tex = true) :
					MeshComponent::MeshComponent(e, &v, color, tex) { };
	~MeshComponent();
};


#endif