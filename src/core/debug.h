#ifndef DEBUG
#define DEBUG
#include "camera.h"
#include "../common.h"
#include "shader.h"
class Debug
{
    private:
        unsigned int VBO;
        unsigned int VAO;
        Shader *linkedShader;
        std::vector<float> vertices;
        void init();
        glm::vec3 start; //Temp
        glm::vec3 end; //Temp
        glm::mat4 model = glm::mat4(1.0);
        

    public:
        void drawLine(glm::vec3 start, glm::vec3 end, VCamera &camera);
        glm::vec3 tint;
        Debug (Shader * lineShader)
        {
            linkedShader = lineShader;
            init();
        }
};

#endif