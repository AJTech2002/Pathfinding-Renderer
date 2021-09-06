#ifndef MESH
#define MESH

#include "../common.h"
#include "shader.h"
#include "vertex.h"


class Mesh {
    
    private:
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
        Shader *linkedShader;

    public:
        glm::vec3 tint = glm::vec3(0.0f, 0.0f, 0.1f);
        glm::vec3 worldPosition = glm::vec3(0.0f);

        std::vector<Vertex> vertices; //Will be modifying these directly 
        std::vector<unsigned int> indices;
        std::vector<Stick> sticks;
        Mesh(){

        }
        Mesh(Shader *meshShader, std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Stick> _sticks);

        void draw(glm::mat4 viewMatrix, glm::mat4 projection, bool wireframe);
};

#endif