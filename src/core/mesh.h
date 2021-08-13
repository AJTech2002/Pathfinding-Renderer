#include "../common.h"
#include "shader.h"

class Mesh
{
    private:
        unsigned int VBO;
        unsigned int VAO;
        Shader *linkedShader;

    public:
        float vertices[9] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
        };

        void draw();
        void init();

        Mesh(Shader* meshShader);
        
};

