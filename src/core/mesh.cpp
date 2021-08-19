#include "mesh.h"


Mesh::Mesh(Shader* meshShader, std::vector<Vertex> verts, std::vector<unsigned int> ind) {
    linkedShader = meshShader;
    vertices = verts;
    indices = ind;
    init();
}


//TODO: Normal data (how to load)

void Mesh::init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    //&vertices[0] is a reference to the first element (an array)
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
    
    //3 for Point
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    
    //3 for Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));
    glEnableVertexAttribArray(1);
}

bool Mesh::TestRayOBBIntersection(
	const Ray &r
){
    return false;
}

void Mesh::draw(VCamera* sceneCamera)
{
    //Set Uniforms for this mesh before the draw
    if (linkedShader != nullptr) {

        linkedShader->use();
        linkedShader->setVec3("tint", tint);
        linkedShader->MVP(model, (*sceneCamera->getViewMatrix()), sceneCamera->projection);
        
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Mesh::drawLine (glm::vec3 start, glm::vec3 end, VCamera *sceneCamera)
{
    if (linkedShader != nullptr) {

        linkedShader->use();
        linkedShader->setVec3("tint", tint);
        linkedShader->MVP(model, (*sceneCamera->getViewMatrix()), sceneCamera->projection);
        
    }

    vertices = std::vector<Vertex>();
    Vertex a;
    a.Position = start;
    Vertex b;
    b.Position = end;
    vertices.push_back(a);
    vertices.push_back(b);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //&vertices[0] is a reference to the first element (an array)
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    
    // glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_LINES, 0, 2);
}

bool Mesh::rayDoesIntersect(Ray &ray)
{
    for(int i=0; i<100; i++){

        float intersection_distance; // Output of TestRayOBBIntersection()
        glm::vec3 aabb_min(-1.0f, -1.0f, -1.0f); //Need to update
        glm::vec3 aabb_max( 1.0f,  1.0f,  1.0f); //Need to update

        if ( TestRayOBBIntersection(ray))
        {
            std::cout << "INTERSECT" << std::endl;
            return true;
        }
    }
    return false;
}
