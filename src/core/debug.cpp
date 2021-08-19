#include "debug.h"

void Debug::init ()
{

    std::cout << "INIT LINE w/ SHADER " << linkedShader->ID << std::endl;

    vertices.clear();
    vertices.push_back(0);
    vertices.push_back(0);
    vertices.push_back(0);
    
    vertices.push_back(0);
    vertices.push_back(5);
    vertices.push_back(0);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_DYNAMIC_DRAW);

    //Location 1 Position Vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

}

void Debug::drawLine(glm::vec3 start, glm::vec3 end, VCamera &camera)
{
    if (linkedShader != nullptr) {


        model = glm::mat4(1.0f);

        linkedShader->use();
        // linkedShader->setVec3("color", tint);
        linkedShader->MVP(model, *(camera.getViewMatrix()), camera.projection);
        
        
    }

    vertices = std::vector<float>();
    vertices.push_back(start.x);
    vertices.push_back(start.y);
    vertices.push_back(start.z);
    
    vertices.push_back(end.x);
    vertices.push_back(end.y);
    vertices.push_back(end.z);
    
    // glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    
    glBindVertexArray(VAO);

    glDrawArrays(GL_LINES, 0, 2);
    
}