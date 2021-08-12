#include "../common.h"
class Mesh
{
    private:
        unsigned int VBO;

    public:
        float vertices[9] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
        };
        
        void draw();

        Mesh();
        
};

