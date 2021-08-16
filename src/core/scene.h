#ifndef SCENE
#define SCENE
#include "../common.h"
#include "model.h"
#include "ray.h"
#include "camera.h"


class Scene {

    public:
        std::vector<Model*> sceneObjects;
        Model* intersectRay(Ray &ray);
        void addSceneObject(Model* sceneObject);
        Ray rayFromSceneCamera(VCamera &camera, glm::vec2 screenPosition, glm::vec2 screenSize);
};

#endif