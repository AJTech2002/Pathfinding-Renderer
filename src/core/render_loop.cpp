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
    Model capsuleModel("C:/Users/Ajay/Desktop/Pathfinding-Renderer/primitives/Cube.fbx",&shader);
    capsuleModel.meshes[0].tint = glm::vec3(107.0 / 256.0f, 190.0 / 256.0f, 242.0 / 256.0f);
    Light directionalLight;

    Mesh debugLine(&shader, std::vector<Vertex>(), std::vector<unsigned int>());

    glfwSetCursorPosCallback(window, mouse_callback);  

    scene.addSceneObject(&capsuleModel);
 
    VCamera camera;

    camera.projection = glm::perspective(glm::radians(60.0f), 800.0f / 800.0f, 0.1f, 1000.0f);

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

        // camera.cameraPos = glm::vec3(glm::sin(glfwGetTime()*0.5f)*10.0f,5.0f, -3.0f);

        capsuleModel.draw(&camera);
        debugLine.drawLine(origin, origin+(rayDir*100.0f), &camera);
        // lineDebug.drawLine(glm::vec3(0, 0, 0), glm::vec3(0, 5, 0), camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }

    glfwTerminate();
    return;
}

float yaw, pitch; 
float lastX, lastY = 400.0f; //Init at Center
bool firstMouse;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
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
    //    std::cout << "Cursor Position at (" << xpos << " : " << ypos << std::endl;
       Ray ray = scene->rayFromSceneCamera(*camera, glm::vec2((float)xpos, (float)ypos), glm::vec2(800.0f, 800.0f));
       rayDir = ray.dir;
       origin = ray.origin;
    //    std::cout << "ORIGIN at ( " << ray.origin.x << "," << ray.origin.y << "," << ray.origin.z << " ) " << std::endl;
    //    std::cout << "DIR at ( " << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << " ) " << std::endl;

       scene->intersectRay(ray);
    }

    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->cameraPos += cameraSpeed * camera->forward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->cameraPos -= cameraSpeed * camera->forward;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->cameraPos -= glm::normalize(glm::cross(camera->forward, camera->up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->cameraPos += glm::normalize(glm::cross(camera->forward, camera->up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera->cameraPos += camera->up * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera->cameraPos -= camera->up * cameraSpeed;


    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera->forward = glm::normalize(direction);

}