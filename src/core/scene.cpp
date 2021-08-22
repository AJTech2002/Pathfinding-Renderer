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


glm::vec3 Scene::screenToWorld (VCamera &camera, glm::vec2 screenPosition, float z, float worldZ, glm::vec2 screenSize, glm::vec3* outVec)
{
    float x = (2.0f * screenPosition.x) / screenSize.x - 1.0f;
    float y = 1.0f - (2.0f * screenPosition.y) / screenSize.y;
    
    //Normalised device coordinates
    glm::vec3 ray_nds = glm::vec3(x, y, z);

    //Forward z is -1.0
    glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);

    glm::vec4 ray_eye = glm::inverse(camera.projection) * ray_clip;

    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, worldZ, 0.0f);

    glm::vec3 ray_world = glm::vec3(glm::inverse(*camera.getViewMatrix()) * ray_eye);

    ray_world = glm::normalize(ray_world);

    *outVec = glm::vec3(ray_world.x, ray_world.y, ray_world.z);
    
}

Ray Scene::rayFromSceneCamera (VCamera &camera, glm::vec2 screenPosition, glm::vec2 screenSize)
{
    Ray testRay;

    // float x = (2.0f * screenPosition.x) / screenSize.x - 1.0f;
    // float y = 1.0f - (2.0f * screenPosition.y) / screenSize.y;
    // float z = 1.0f;
    
    // //Normalised device coordinates
    // glm::vec3 ray_nds = glm::vec3(x, y, z);

    // //Forward z is -1.0
    // glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);

    // glm::vec4 ray_eye = glm::inverse(camera.projection) * ray_clip;

    // ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

    // glm::vec3 ray_world = glm::vec3(glm::inverse(*camera.getViewMatrix()) * ray_eye);

    // ray_world = glm::normalize(ray_world);

    glm::vec3 tempPoint;
    glm::vec3 center;

    screenToWorld(camera, screenPosition, -1.0f, 0.0f, screenSize, &center);
    screenToWorld(camera, screenPosition, 1.0f, -1.0f, screenSize, &tempPoint);

    testRay.dir = tempPoint;

    printf("%2f, %2f, %2f \n", testRay.dir.x, testRay.dir.y, testRay.dir.z);

    testRay.origin = camera.cameraPos;

    return testRay;
}