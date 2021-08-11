#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "setup/program_setup.h"
#include <iostream>
#include "core/render_loop.h"

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow *currentWindow;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	currentWindow = CreateWindow(SCR_WIDTH, SCR_WIDTH);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glfwSetFramebufferSizeCallback(currentWindow, framebuffer_size_callback);

	renderLoop(currentWindow);

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
