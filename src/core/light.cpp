#include "light.h"

Light::Light() {
    direction = glm::vec3(1.2f, 1.0f, 2.0f);
    position = glm::vec3(2.0f, 2.0f, 1.5f);
    ambient = glm::vec3(0.2f, 0.2f, 0.2f);
}

void Light::applyLightingUniforms (Shader* shader, VCamera* camera)
{
    //Pass lighting uniforms into shader
    if (!directional)
    {
        //Position doesn't get included in intensity
        shader->setVec3("lightPosition", position);
        shader->setVec3("lightAmbience", ambient);
        shader->setFloat("lightIntensity", intensity);
        shader->setVec3("lightColor", color);

        shader->setVec3("viewPos", camera->cameraPos);
    }
}