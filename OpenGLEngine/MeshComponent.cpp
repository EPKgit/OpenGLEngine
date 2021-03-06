#include "MeshComponent.hpp"

MeshComponent::MeshComponent(std::weak_ptr<Entity> e) : Component(e)
{
	type = constants::ComponentType::MeshComponent;
}

MeshComponent::MeshComponent(std::weak_ptr<Entity> e, std::vector<float> *v, std::vector<unsigned int> *i, bool color, bool tex) 
	: MeshComponent::MeshComponent(e, v, color, tex)
{
	mType = MeshType::VertsPlusIndices;
	std::move(i->begin(), i->end(), std::back_inserter(indices));
	numElements = indices.size();
	glGenBuffers(1, &EBO);//create our EBO buffer
	glBindVertexArray(VAO); //set our VAO as the active VAO buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//bind our EBO into our VAO and set it as our active buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);//write our index data into our EBO
	glBindVertexArray(VAO);//unbind our VAO just in case
}

MeshComponent::MeshComponent(std::weak_ptr<Entity> e, std::vector<float> *v, bool color, bool tex) : MeshComponent::MeshComponent(e)
{
	mType = MeshType::VertsOnly;
	std::move(v->begin(), v->end(), std::back_inserter(verts));
	glGenVertexArrays(1, &VAO); //creates our VAO buffer
	glGenBuffers(1, &VBO);//creates the VBO buffer

	glBindVertexArray(VAO); //set our VAO as the active VAO buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //set our VBO as the active VBO buffer / binds our new buffer to GL_ARRAY_BUFFER
										//also attaches our VBO into our VAO
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), &verts[0], GL_STATIC_DRAW);//sends our vertex data to our VBO

	int step = 3;
	step += (color) ? 3 : 0 + (tex) ? 2 : 0;
	numElements = verts.size() / step;
	int currentOffset = 0;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, step * sizeof(float), (void*)currentOffset);	//store our vertex attribute data into the current buffer which is currently our VBO
	glEnableVertexAttribArray(0); //sets our vertex attribute usable
	currentOffset += 3;
	if (color)
	{
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, step * sizeof(float), (void*)(currentOffset * sizeof(float)));
		glEnableVertexAttribArray(1);
		currentOffset += 3;
	}
	if (tex)
	{
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, step * sizeof(float), (void*)(currentOffset * sizeof(float)));
		glEnableVertexAttribArray(2);
		currentOffset += 2;
	}
	glBindVertexArray(VAO);//unbind our VAO just in case
}



MeshComponent::~MeshComponent()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	switch (mType)
	{
	case MeshType::VertsPlusIndices:
		glDeleteBuffers(1, &EBO);
		break;
	case MeshType::VertsOnly:
		break;
	}
}