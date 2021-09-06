#include "common.h"
#include "setup/program_setup.h"
#include  "render.h"

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow *currentWindow;

int main()
{
  
  glfwInit();
    

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

  currentWindow = CreateGLWindow(SCR_WIDTH, SCR_WIDTH);

  glewInit();

  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

  glfwSetFramebufferSizeCallback(currentWindow, framebuffer_size_callback);

  glfwSetInputMode(currentWindow, GLFW_CURSOR, GLFW_VISIBLE);

  render_window(currentWindow);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
