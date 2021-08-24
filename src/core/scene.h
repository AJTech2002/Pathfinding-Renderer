#ifndef SCENE
#define SCENE
#include "../common.h"
#include "model.h"
#include "ray.h"
#include "camera.h"
#include "light.h"
#include "shader.h"


//The scene owns these properties now, no longer references

class Scene {

    public:
        std::vector<Model> sceneObjects;
        std::vector<Shader> sceneShaders;
        Light directionalLight;
        VCamera sceneCamera;
        
        void setupScene (Light _directionalLight, VCamera _sceneCamera)
        {
            directionalLight = _directionalLight;
            sceneCamera = _sceneCamera;
        }

        void drawScene();

        Model *intersectRay(Ray &ray, RayHit &hit);
        void addSceneObject(Model sceneObject);
        Ray rayFromSceneCamera(VCamera &camera, glm::vec2 screenPosition, glm::vec2 screenSize);
        glm::vec3 screenToWorld(VCamera &camera, glm::vec2 screenPosition, float z, float worldZ, glm::vec2 screenSize, glm::vec3 *outVec);
};

#endif