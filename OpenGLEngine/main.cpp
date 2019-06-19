#include <iostream>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"
#include "Structs.hpp"
#include "Constants.hpp"
#include "InputSystem.hpp"
#include "Shader.hpp"

void window_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, constants::screenWidth, constants::screenHeight);
}

void GLFWstartup()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void PROCESSINPUT_TEMP(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void GameLoop(GLFWwindow * window)
{
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	float texCoords[] = {
		0.0f, 0.0f,  // lower-left corner  
		1.0f, 0.0f,  // lower-right corner
		0.5f, 1.0f   // top-center corner
	};
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	glGenVertexArrays(1, &VAO); //creates our VAO buffer
	glGenBuffers(1, &VBO);//creates the VBO buffer
	glGenBuffers(1, &EBO);//create our EBO buffer

	glBindVertexArray(VAO); //set our VAO as the active VAO buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //set our VBO as the active VBO buffer / binds our new buffer to GL_ARRAY_BUFFER
										//also attaches our VBO into our VAO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//sends our vertex data to our VBO
	
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//bind our EBO into our VAO and set it as our active buffer
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//write our index data into our EBO
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	//store our vertex attribure data into the current buffer which is currently our VBO
	glEnableVertexAttribArray(0); //sets our vertex attribute usable
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO);//unbind our VAO just in case

	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);//set our border color
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//set how we want to deal with images that are too small
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);//ext lib to load file as char[]
	unsigned int texture;//ID for our texture
	glGenTextures(1, &texture);//generate an ID for our texture
	
	Shader s("BaseVertex.shader", "BaseFragment.shader");
	s.Use();
	

	while (!glfwWindowShouldClose(window))
	{
		PROCESSINPUT_TEMP(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

int main()
{
	GLFWstartup();
	GLFWwindow * window = glfwCreateWindow(constants::screenWidth, constants::screenHeight, "Testing", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, constants::screenWidth, constants::screenHeight);
	glfwSetFramebufferSizeCallback(window, window_resize_callback);

	GameLoop(window);

	return 0;
}