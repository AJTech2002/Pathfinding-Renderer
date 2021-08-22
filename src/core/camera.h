#ifndef CAMERA
#define CAMERA

#include "../common.h"

class VCamera 
{
    public:
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), 800.0f/800.0f, 0.1f, 1000.0f);
    
        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4* getViewMatrix();

        VCamera();

    private:
        glm::mat4 view;
        
};

#endif