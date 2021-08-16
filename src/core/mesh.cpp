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


bool Mesh::rayDoesIntersect(Ray &ray)
{
    Ray modifiedRay;

    glm::mat4 inverseModel = glm::inverse(model); //Should store this

    // //Modify the ray into model space
    // modifiedRay.dir = glm::vec3(inverseModel * glm::vec4(ray.dir,0.0f));
    // modifiedRay.origin = glm::vec3(inverseModel * glm::vec4(ray.origin, 1.0f));

    for (int i = 0; i < indices.size(); i++)
    {
        Vertex* v1 = &vertices[indices[i]];
        i++;
        Vertex* v2 = &vertices[indices[i]];
        i++;
        Vertex* v3 = &vertices[indices[i]];
        
        if (doesIntersectTriangle(v1, v2, v3, ray)) {
            std::cout << "RAY INTERSECTS MESH" << std::endl;
            return true;
        }
    }

    return false;
}

glm::vec3 Mesh::worldCoordinate(glm::vec3 modelCoordinate)
{
    return glm::vec3(model * glm::vec4(modelCoordinate, 1.0f));
}

bool Mesh::doesIntersectTriangle (Vertex* v1, Vertex* v2, Vertex* v3, Ray &ray)
{
    glm::vec3 intersectionPointOfPlaneRay = IntersectPlane(ray, worldCoordinate(v1->Position),  worldCoordinate(v2->Position),  worldCoordinate(v3->Position));
    return PointInTriangle(intersectionPointOfPlaneRay, worldCoordinate(v1->Position),  worldCoordinate(v2->Position),  worldCoordinate(v3->Position));
}

glm::vec3 Mesh::IntersectPlane(Ray &ray, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2)
{
    glm::vec3 D = glm::vec3(ray.dir.x, ray.dir.y, ray.dir.z);
    glm::vec3 N = glm::cross(p1-p0, p2-p0);
    glm::vec3 X = ray.origin + D * glm::dot(p0 - ray.origin, N) / glm::dot(D, N);

    return X;
}

float Mesh::PointInOrOn (glm::vec3 p1, glm::vec3 p2, glm::vec3 start, glm::vec3 end)
{
    glm::vec3 cp1 = glm::cross(end - start, p1 - start);
    glm::vec3 cp2 = glm::cross(end - start, p2 - start);
    
    if (glm::dot(cp1, cp2) >= 0.0f) return glm::dot(cp1, cp2);
    else
        return 0.0f;
}

bool Mesh::PointInTriangle (glm::vec3 px, glm::vec3 p0, glm::vec3 p1,glm::vec3 p2)
{
    return 
        PointInOrOn(px, p0, p1, p2) *
        PointInOrOn(px, p1, p2, p0) *
        PointInOrOn(px, p2, p0, p1);
}

void Mesh::draw(VCamera* sceneCamera)
{
    //Set Uniforms for this mesh before the draw
    if (linkedShader != nullptr) {
        linkedShader->setVec3("tint", tint);
        linkedShader->MVP(model, (*sceneCamera->getViewMatrix()), sceneCamera->projection);
        linkedShader->use();
    }

    glBindVertexArray(VAO);
    
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
}