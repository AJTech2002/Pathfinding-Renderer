#include "camera.h"

VCamera::VCamera(){}

glm::mat4* VCamera::getViewMatrix ()
{
    
    // glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    
    glm::vec3 cameraDirection = glm::normalize(forward);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    
    view = glm::lookAt(cameraPos, cameraPos+forward, cameraUp);
   
    return &view;
}