#include "render_loop.h"
#include "mesh.h"
#include "debug.h"
#include "model.h"

glm::vec3 rayDir = glm::vec3(0.0f);
glm::vec3 origin = glm::vec3(1.0f);

void renderLoop(GLFWwindow* window)
{

    Shader shader("C:/Users/Ajay/Desktop/Pathfinding-Renderer/src/shaders/vertex.glsl", "C:/Users/Ajay/Desktop/Pathfinding-Renderer/src/shaders/fragment.glsl");
    Shader lineShader("C:/Users/Ajay/Desktop/Pathfinding-Renderer/src/shaders/lineVertex.glsl", "C:/Users/Ajay/Desktop/Pathfinding-Renderer/src/shaders/lineFragment.glsl");
 
    Scene scene;
    Model capsuleModel("C:/Users/Ajay/Desktop/Pathfinding-Renderer/primitives/CapsuleSmooth.fbx",&shader);
    capsuleModel.meshes[0].tint = glm::vec3(107.0 / 256.0f, 190.0 / 256.0f, 242.0 / 256.0f);
    Light directionalLight;

    Mesh debugLine(&shader, std::vector<Vertex>(), std::vector<unsigned int>());



    scene.addSceneObject(&capsuleModel);
 
    VCamera camera;

    std::cout << "Test Output \n";

    glLineWidth(2.0f);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window, &scene, &camera);
        
        // Rendering
        glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        

        //Apply lighting to the global shader (doesn't have to be done for each object as global)
        directionalLight.applyLightingUniforms(&shader, &camera);

        camera.cameraPos = glm::vec3(glm::sin(glfwGetTime()*0.5f)*10.0f,0.0f, -3.0f);

        capsuleModel.draw(&camera);
        debugLine.drawLine(origin, origin+(rayDir*10.0f), &camera);
        // lineDebug.drawLine(glm::vec3(0, 0, 0), glm::vec3(0, 5, 0), camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }

    glfwTerminate();
    return;
}



void processInput(GLFWwindow *window, Scene* scene, VCamera* camera)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        double xpos, ypos;
       //getting cursor position
       glfwGetCursorPos(window, &xpos, &ypos);
       std::cout << "Cursor Position at (" << xpos << " : " << ypos << std::endl;
       Ray ray = scene->rayFromSceneCamera(*camera, glm::vec2((float)xpos, (float)ypos), glm::vec2(800.0f, 600.0));
       rayDir = ray.dir;
       origin = ray.origin;
       std::cout << "ORIGIN at ( " << ray.origin.x << "," << ray.origin.y << "," << ray.origin.z << " ) " << std::endl;
       std::cout << "DIR at ( " << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << " ) " << std::endl;

       scene->intersectRay(ray);
    }
}