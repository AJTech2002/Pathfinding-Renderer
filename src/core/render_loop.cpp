#include "render_loop.h"
#include "mesh.h"
#include "debug.h"
#include "model.h"

#pragma region Scene Properties

glm::vec3 rayDir = glm::vec3(0.0f);
glm::vec3 origin = glm::vec3(1.0f);

Scene scene;

#pragma endregion

void renderLoop(GLFWwindow* window)
{
    initScene();
    
    glfwSetCursorPosCallback(window, mouse_callback);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window, &scene, &scene.sceneCamera);

        // Rendering
        glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        onUpdate();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return;
}

glm::vec2 lastPos;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    glm::vec2 curPos(xpos, ypos);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
    {

    }

}

void onUpdate()
{
    //Game Logic & Scene Draw
    scene.drawScene();
}

Model *debug;

void initScene ()
{
    Shader shader("C:/Users/Ajay/Desktop/Pathfinding-Renderer/src/shaders/vertex.glsl", "C:/Users/Ajay/Desktop/Pathfinding-Renderer/src/shaders/fragment.glsl");

    scene.sceneShaders.push_back(shader);

    Model capsuleModel("C:/Users/Ajay/Desktop/Pathfinding-Renderer/primitives/CapsuleSmooth.fbx", &scene.sceneShaders[0]);
    
    debug = new Model ("C:/Users/Ajay/Desktop/Pathfinding-Renderer/primitives/DebugSphere.fbx", &scene.sceneShaders[0]);

    Light directionalLight;
    
    VCamera camera;

    scene.setupScene(directionalLight, camera);

    capsuleModel.meshes[0].tint = glm::vec3(107.0 / 256.0f, 190.0 / 256.0f, 242.0 / 256.0f);
    // capsuleModel.meshes[0].model = glm::scale(capsuleModel.meshes[0].model, glm::vec3(0.3f, 1.5f, 2.0f));
    scene.addSceneObject(capsuleModel);
    scene.addSceneObject(*debug);

    debug = &scene.sceneObjects[1];

    camera.projection = glm::perspective(glm::radians(60.0f), 800.0f / 800.0f, 0.1f, 1000.0f);
    glLineWidth(2.0f);
}

std::string debugVec3 (glm::vec3 vec)
{
    return (std::to_string(vec.x) + "," + std::to_string(vec.y) + "," + std::to_string(vec.z));
}

void processInput(GLFWwindow *window, Scene* scene, VCamera* camera)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
       double xpos, ypos;
       glfwGetCursorPos(window, &xpos, &ypos);
       Ray ray = scene->rayFromSceneCamera(*camera, glm::vec2((float)xpos, (float)ypos), glm::vec2(800.0f, 800.0f));
       rayDir = ray.dir;
       origin = ray.origin;

       RayHit hit;

       scene->intersectRay(ray, hit);
        
        glm::mat4 identity(1.0f);
        if (debug != nullptr) {
            std::cout << "Intersection Point : " << debugVec3(hit.hitPoint) << " Distance : " << glm::distance(hit.hitPoint, origin) << std::endl;
            debug->meshes[0].model = glm::scale(glm::translate(identity, glm::vec3(hit.hitPoint)), glm::vec3(0.2f));
            
        }

       
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

}