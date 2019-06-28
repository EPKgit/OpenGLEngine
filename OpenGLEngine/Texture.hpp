#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP

#include <glad/glad.h>

class Texture
{
public:
	Texture(const char * filename, unsigned int = GL_RGB, unsigned int = GL_RGB, bool = false);
	void Use();
	unsigned int GetID();
private:
	unsigned int texture;
};

#endif // !_TEXTURE_HPP

