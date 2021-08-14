#include "../common.h"
#include "shader.h"
#include "camera.h"

class Mesh
{
    private:
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
        Shader *linkedShader;

    public:
        glm::vec3 tint = glm::vec3(1.0f); //Todo: move to material object
        
        //Abstract the position out from the Model, Light & Camera to be a GO
        glm::mat4 model = glm::mat4(1.0f);

        void draw(VCamera* sceneCamera);
        void init();

        Mesh(Shader* meshShader);
        
};

