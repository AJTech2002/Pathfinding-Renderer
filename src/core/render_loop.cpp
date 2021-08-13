#include "render_loop.h"
#include "mesh.h"

void renderLoop(GLFWwindow* window)
{

    Shader shader ("src/shaders/vertex.glsl","src/shaders/fragment.glsl");
    Mesh mesh(&shader);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        //rendering

        glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mesh.draw();

        mesh.vertices[0] -= 0.001;

        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }

    glfwTerminate();
    return;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}