#ifndef _SHADER_HPP
#define _SHADER_HPP

#include <string>
#include <fstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader() {};
	Shader(const char * vFilename, const char * fFilename) { Setup(vFilename, fFilename); }
	void Setup(const char * vFilename, const char * fFilename) { CreateMyShaderProgram(ID, vFilename, fFilename); }
	void SetBool(const char * name, const bool b) const;
	void SetInt(const char * name, const int i) const;
	void SetFloat(const char * name, const float f) const;
	void setVec2(const char * name, const glm::vec2 &value) const;
	void setVec2(const char * name, float x, float y) const;
	void setVec3(const char * name, const glm::vec3 &value) const;
	void setVec3(const char * name, float x, float y, float z) const;
	void setVec4(const char * name, const glm::vec4 &value) const;
	void setVec4(const char * name, float x, float y, float z, float w) const;
	void setMat2(const char * name, const glm::mat2 &mat) const;
	void setMat3(const char * name, const glm::mat3 &mat) const;
	void setMat4(const char * name, const glm::mat4 &mat) const;
	void Use();
	unsigned int GetID();
private:
	unsigned int ID;
	std::string ReadShaderFile(const char * filename);
	bool SetupShader(unsigned int &i, const char * filename, GLenum shaderType);
	bool SetupShaderProgram(unsigned int &i, unsigned int shaderArr[], int n);
	bool CreateMyShaderProgram(unsigned int &shaderProgram, const char * vFilename, const char * fFilename);
};

#endif //_SHADER_HPP