#include "Shader.hpp"

unsigned int Shader::GetID()
{
	return ID;
}

void Shader::SetBool(const char * name, const bool b) const
{
	glUniform1i(glGetUniformLocation(ID, name), b);
}

void Shader::SetInt(const char * name, const int i) const
{
	glUniform1i(glGetUniformLocation(ID, name), i);
}

void Shader::SetFloat(const char * name, float f) const
{
	glUniform1i(glGetUniformLocation(ID, name), (GLint)f);
}
void Shader::setVec2(const char * name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
void Shader::setVec2(const char * name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name), x, y);
}
void Shader::setVec3(const char * name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
void Shader::setVec3(const char * name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}
void Shader::setVec4(const char * name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
void Shader::setVec4(const char * name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}
void Shader::setMat2(const char * name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat3(const char * name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat4(const char * name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::Use()
{
	glUseProgram(ID);
}

std::string Shader::ReadShaderFile(const char * filename)
{
	std::string workstring;
	std::string keep;
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cout << "ERROR CANNOT OPEN SHADER FILE" << std::endl;
		return std::string();
	}
	while (std::getline(file, workstring))
	{
		keep.append(workstring);
		keep += '\n';
	}
	return keep;
}

bool Shader::SetupShader(unsigned int &i, const char * filename, GLenum shaderType)
{
	i = glCreateShader(shaderType);
	std::string source = ReadShaderFile(filename);
	const char * c = source.c_str();
	glShaderSource(i, 1, &c, NULL); //pass it our source code
	glCompileShader(i);//attempt to compile
	int success;
	char infoLog[512];
	glGetShaderiv(i, GL_COMPILE_STATUS, &success); //fetch if we succeeded
	if (!success)
	{
		glGetShaderInfoLog(i, 512, NULL, infoLog);
		std::cout << "ERROR SHADER COMPILATION FAILED WITH LOG\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

bool Shader::SetupShaderProgram(unsigned int &i, unsigned int shaderArr[], int n)
{
	int success;
	char infoLog[512];
	i = glCreateProgram(); //create the shader program
	for (int x = 0; x < n; ++x)
	{
		glAttachShader(i, shaderArr[x]); //attach all of our shaders to it
	}
	glLinkProgram(i);//link it
	glGetProgramiv(i, GL_LINK_STATUS, &success); //check if successfully compiledd
	if (!success)
	{
		glGetProgramInfoLog(i, 512, NULL, infoLog);
		std::cout << "ERROR SHADER PROGRAM COMPILATION FAILED WITH LOG\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

bool Shader::CreateMyShaderProgram(unsigned int &shaderProgram, const char * vFilename, const char * fFilename)
{
	unsigned int vertexShader;
	if (!SetupShader(vertexShader, vFilename, GL_VERTEX_SHADER))
	{
		return false;
	}
	unsigned int fragShader;
	if (!SetupShader(fragShader, fFilename, GL_FRAGMENT_SHADER))
	{
		return false;
	}
	unsigned int arr[] = { vertexShader, fragShader };
	if (!SetupShaderProgram(shaderProgram, arr, 2))
	{
		return false;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
	return true;
}