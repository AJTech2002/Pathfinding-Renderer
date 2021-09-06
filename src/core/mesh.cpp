#include "mesh.h"

Mesh::Mesh(Shader *meshShader, std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Stick> _sticks)
{
    linkedShader = meshShader;
    sticks = _sticks;
    vertices = _vertices;
    indices = _indices;
    

    // Pointers to Location in Vertex Buffers
    glGenVertexArrays(1, &VAO);

    // Physical Buffers
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Binding the VAO & VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);

    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);

    //3 for Point
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    
    //3 for Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));
    glEnableVertexAttribArray(1);
}

void Mesh::draw (glm::mat4 viewMatrix, glm::mat4 projection, bool wireframe)
{
    if (linkedShader != nullptr)
    {
        linkedShader->use();
        linkedShader->setVec3("tint", tint);
        linkedShader->MVP(glm::mat4(1.0), viewMatrix, projection);
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    //Reset the positions data

    // printf("%2f, %2f, %2f \n", vertices[1].Position.x, vertices[1].Position.y, vertices[1].Position.z);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);

    glBindVertexArray(VAO);
    
    // glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    if (!wireframe)
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    else
    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
}

 