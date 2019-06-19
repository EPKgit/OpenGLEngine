#ifndef _SHADER_HPP
#define _SHADER_HPP

#include <string>
#include <fstream>
#include <iostream>

#include <glad/glad.h>

class Shader
{
public:
	Shader(const char * vFilename, const char * fFilename);
	void SetBool(const char * name, bool b);
	void SetInt(const char * name, int i);
	void SetFloat(const char * name, float f);
	void Use();
private:
	unsigned int ID;
	std::string ReadShaderFile(const char * filename);
	bool SetupShader(unsigned int &i, const char * filename, GLenum shaderType);
	bool SetupShaderProgram(unsigned int &i, unsigned int shaderArr[], int n);
	bool CreateMyShaderProgram(unsigned int &shaderProgram, const char * vFilename, const char * fFilename);
};

#endif //_SHADER_HPP