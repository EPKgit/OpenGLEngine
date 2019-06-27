#include "Texture.hpp"

Texture::Texture(const char * filename, unsigned int storageFormat /*= GL_RGB*/,
				 unsigned int sourceFormat /*= GL_RGB*/, bool shouldFlip /*= false*/)
{
	int width, height, nrChannels;
	unsigned char *data;
	glGenTextures(1, &texture);//generate an ID for our texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(shouldFlip); // tell stb_image.h to flip loaded texture's on the y-axis.
	data = stbi_load(filename, &width, &height, &nrChannels, 0);//ext lib to load file as char[]
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, storageFormat, width, height, 0, sourceFormat, GL_UNSIGNED_BYTE, data);
		//enum target, mipmap lvl, storage format, w/h, legacy var, source format(2), array pointer
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR FAILED TO LOAD TEXTURE" << std::endl;
	}
	stbi_image_free(data);
}

void Texture::Use()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}

unsigned int Texture::GetID()
{
	return texture;
}