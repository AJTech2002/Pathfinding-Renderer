#include "scene.h"

void Scene::addSceneObject (Model* model)
{
    sceneObjects.push_back(model);
}

Model* Scene::intersectRay (Ray &ray)
{
    Model *returnModel = nullptr;

    for (int i = 0; i < sceneObjects.size(); i++)
    {
        if (sceneObjects[i]->didIntersectAnyMeshes(ray))
            return sceneObjects[i]; //Returns the first (but not in Z depth)
    }

    return returnModel;
}

Ray Scene::rayFromSceneCamera (VCamera &camera, glm::vec2 screenPosition, glm::vec2 screenSize)
{
    Ray testRay;

    float x = (2.0f * screenPosition.x) / screenSize.x - 1.0f;
    float y = 1.0f - (2.0f * screenPosition.y) / screenSize.y;
    float z = 1.0f;
    
    //Normalised device coordinates
    glm::vec3 ray_nds = glm::vec3(x, y, z);

    //Forward z is -1.0
    glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);

    glm::vec4 ray_eye = glm::inverse(camera.projection) * ray_clip;

    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

    glm::vec3 ray_world = glm::vec3(glm::inverse(*camera.getViewMatrix()) * ray_eye);

    ray_world = glm::normalize(ray_world);

    // ray_world.x *= 1000.0f;
    // ray_world.y *= 1000.0f;
    // ray_world.z *= 1000.0f;
    

    testRay.origin = camera.cameraPos;
    testRay.dir = ray_world;
    

    return testRay;
}