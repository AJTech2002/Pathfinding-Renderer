#include "mesh.h"

Mesh::Mesh(Shader* meshShader) {
    linkedShader = meshShader;
}

void Mesh::init()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Mesh::draw()
{
   // 0. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    linkedShader->use();

    glBindVertexArray(VAO);
    
    
    glDrawArrays(GL_TRIANGLES, 0, 3); 
}