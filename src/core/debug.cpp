#include "debug.h"

void Debug::drawLine(glm::vec3 start, glm::vec3 end, VCamera &camera)
{
    glBegin(GL_LINES);
    
    glm::vec3 projected = glm::vec3(camera.projection * (*camera.getViewMatrix()) * glm::vec4(start, 1.0f));
    glm::vec3 projectedEnd = glm::vec3(camera.projection * (*camera.getViewMatrix()) * glm::vec4(end, 1.0f));
    
    //No way this works
    glVertex2f(projected.x, projected.y);
    glVertex2f(projected.x, projected.y);

    glEnd();
}