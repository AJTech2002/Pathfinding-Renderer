#include "render_loop.h"
#include "mesh.h"

void renderLoop(GLFWwindow* window)
{

    Shader shader ("C:/Users/Ajay/Desktop/Pathfinding-Renderer/src/shaders/vertex.glsl","C:/Users/Ajay/Desktop/Pathfinding-Renderer/src/shaders/fragment.glsl");
    Mesh mesh(&shader);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        //rendering

        glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
                
        glm::mat4 testTrans = glm::mat4(1.0);

        testTrans = glm::translate(testTrans, glm::vec3(0.5f, -0.5f, 0.0f));
        testTrans = glm::rotate(testTrans, (float)glfwGetTime()*4, glm::vec3(1.0f, 0.0f, 0.0f));

        shader.setMat4("transform", testTrans);

        mesh.draw();


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