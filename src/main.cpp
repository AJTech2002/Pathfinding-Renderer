#include "common.h"
#include "core/render_loop.h"
#include "setup/program_setup.h"

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

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

  renderLoop(currentWindow);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
