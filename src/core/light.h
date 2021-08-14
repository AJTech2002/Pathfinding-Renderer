#ifndef LIGHT
#define LIGHT

#include "camera.h"
#include "../common.h"
#include "shader.h"

class Light {

    public:
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 direction = glm::vec3(0.0f);
        glm::vec3 ambient = glm::vec3(0.3f);
        float intensity = 0.8f;
        bool directional = false;
        glm::vec3 color = glm::vec3(1.0f);

        void applyLightingUniforms(Shader* shader, VCamera* camera);

        Light();
};

#endif