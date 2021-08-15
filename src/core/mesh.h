#include "../common.h"
#include "shader.h"
#include "camera.h"
#include "vertex.h"

class Mesh
{
    private:
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
        Shader *linkedShader;

    public:
        glm::vec3 tint = glm::vec3(1.0f); //Todo: move to material object
        glm::mat4 model = glm::mat4(1.0f);
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices; 
        
        void draw(VCamera* sceneCamera);
        void init();

        Mesh(Shader *meshShader, std::vector<Vertex> vertices, std::vector<unsigned int> indices);
};

