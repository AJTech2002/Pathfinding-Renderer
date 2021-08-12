#include "program_setup.h"
#include <iostream>

GLFWwindow* CreateGLWindow (unsigned  int& width, unsigned int& height)
{
    GLFWwindow *window = glfwCreateWindow(width, height, "Pathfinding Renderer", NULL, NULL);
    
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW Window \n";
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    std::cout << "Window Created \n";

    return window;
} 
