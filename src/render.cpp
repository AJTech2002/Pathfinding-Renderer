#ifndef RENDER
#define RENDER
#include "render.h"
#include "common.h"
#include "core/mesh.h"
#include "core/shader.h"
#include "core/vertex.h"
#include "cloth_gen.h"
#include "core/sphere.h"
GLFWwindow *window;



//Camera Properties
glm::mat4 projection = glm::perspective(glm::radians(60.0f), 800.0f/800.0f, 0.1f, 1000.0f);
glm::mat4 model = glm::mat4(1.0f); //View Matrix

void setCameraLookAt (glm::vec3 pos, glm::vec3 target, glm::vec3 up)
{
    model = glm::lookAt(pos, target, up);
}

struct input_data {
    bool mouse_down;
    glm::vec2 mousePosition;
};

input_data inputs;

void processInput ()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    //Input Code 
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        inputs.mousePosition = glm::vec2((float)xpos, (float)ypos);
        inputs.mouse_down = true;
    }
    else {
        inputs.mouse_down = false;
    }
}

//wait 3 seconds
int frame = 0;
void render_window (GLFWwindow* _window)
{
    window = _window;
    glEnable(GL_DEPTH_TEST);
    setCameraLookAt(glm::vec3(0, -2.0f, -15.0f), glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    Shader shader("./src/shaders/vertex.glsl", "./src/shaders/fragment.glsl");

    Sphere sphere;
    sphere.center = glm::vec3(0.0f, -5.0f, 0.0f);
    sphere.radius = 3.0f;

    std::vector<Vertex> verts;
    std::vector<unsigned int> indices;
    std::vector<Stick> sticks;
    
    //Orient the cloth looking down
    glm::mat4 identity(1.0f);
    identity = glm::rotate(identity, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    generate_cloth_mesh(20, 20, 1.0f/2.0f, glm::vec3(-5, 3, 0.0f), &shader, verts, indices, sticks, identity);
    
    glLineWidth(1);
    Mesh testCloth(&shader, verts, indices, sticks);

    printf("Number of Verts %d \n", testCloth.vertices.size());
    float deg = 0;
    while (!glfwWindowShouldClose(window))
    {
        frame += 1;
        //Debug Loop
        processInput();
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // Rendering Code (Just cloth and sphere)

        // testCloth.vertices[0].Position = glm::vec3(-5 + glm::sin(glfwGetTime()) * 5, 3, 0.0f);
        
        if (frame > 60) {
            
            simulate(&testCloth, &sphere);
        }

        testCloth.tint = glm::vec3(130.0f/255.0f, 220.0f/255.0f, 255.0f/255.0f);
        testCloth.draw(model, projection,false);
        testCloth.tint = glm::vec3(0.0f, 0.0f, 1.1f);
        testCloth.draw(model, projection,true);

        model = glm::rotate(model, glm::radians(0.2f), glm::vec3(0, 1, 0));

         glfwSwapBuffers(window);
        glfwPollEvents();
    }

}

#endif