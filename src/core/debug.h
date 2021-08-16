#ifndef DEBUG
#define DEBUG
#include "camera.h"
#include "../common.h"

class Debug
{
    public:
        void drawLine(glm::vec3 start, glm::vec3 end, VCamera &camera);
};

#endif