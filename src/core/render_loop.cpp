#include "render_loop.h"
#include "mesh.h"

#include "model.h"
void renderLoop(GLFWwindow* window)
{

    Shader shader("C:/Users/Ajay/Desktop/Pathfinding-Renderer/src/shaders/vertex.glsl", "C:/Users/Ajay/Desktop/Pathfinding-Renderer/src/shaders/fragment.glsl");
    // Mesh mesh(&shader, finalCubeVerts, finalCubeIndices);
    Scene scene;
    Model capsuleModel("C:/Users/Ajay/Desktop/Pathfinding-Renderer/primitives/CapsuleSmooth.fbx",&shader);
    capsuleModel.meshes[0].tint = glm::vec3(107.0 / 256.0f, 190.0 / 256.0f, 242.0 / 256.0f);
    Light directionalLight;

    scene.addSceneObject(&capsuleModel);
    // mesh.tint = glm::vec3(129.0f/256.0f, 242.0f/256.0f, 107.0f/256.0f);

    // Mesh mesh2(&shader, finalCubeVerts, finalCubeIndices);

    // mesh2.tint = glm::vec3(107.0/256.0f, 190.0/256.0f, 242.0/256.0f);

    // Mesh lightMesh(&shader, finalCubeVerts, finalCubeIndices);
    // lightMesh.model = glm::mat4(1.0f);
    // lightMesh.model = glm::translate(lightMesh.model, directionalLight.position);
    // lightMesh.model = glm::scale(lightMesh.model, glm::vec3(0.2f, 0.2f, 0.2f));

    // lightMesh.tint = glm::vec3(1.0f, 1.0f, 1.0f);

    VCamera camera;

    std::cout << "Test Output \n";

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window, &scene, &camera);
        
        // Rendering
        glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //Apply lighting to the global shader (doesn't have to be done for each object as global)
        directionalLight.applyLightingUniforms(&shader, &camera);
        
        //directionalLight.position = glm::vec3(glm::sin(glfwGetTime()*0.5f)*2.0f,glm::cos(glfwGetTime()*0.5f)*2.0f, 1.5f);

        // lightMesh.model = glm::mat4(1.0f);
        // lightMesh.model = glm::translate(lightMesh.model, directionalLight.position);
        // lightMesh.model = glm::scale(lightMesh.model, glm::vec3(0.2f, 0.2f, 0.2f));

        camera.cameraPos = glm::vec3(glm::sin(glfwGetTime()*0.5f)*10.0f,0.0f, -3.0f);
        // mesh.model = glm::mat4(1.0f);
        // mesh.model = glm::rotate(mesh.model,(float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));

        capsuleModel.draw(&camera);

        // mesh2.model = glm::mat4(1.0f);
        // mesh2.model = glm::translate(mesh2.model, glm::vec3(-3.0f, 0.0f, 5.0f));
        // mesh2.model = glm::rotate(mesh2.model,(float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));

        // mesh.draw(&camera);
        // mesh2.draw(&camera);

        // lightMesh.draw(&camera);

        //Swap Buffers
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

       std::cout << "ORIGIN at ( " << ray.origin.x << "," << ray.origin.y << "," << ray.origin.z << " ) " << std::endl;
       std::cout << "DIR at ( " << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << " ) " << std::endl;

       scene->intersectRay(ray);
    }
}