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
	const Ray &r, //Ray into Object
    glm::vec3 min, //Object
    glm::vec3 max //Object
){

    float tmin = (min.x - r.origin.x) / r.dir.x; 
    float tmax = (max.x - r.origin.x) / r.dir.x; 
 
    if (tmin > tmax) {
        float temp = tmin;
        tmin = tmax;
        tmax = temp;
    }
 
    float tymin = (min.y - r.origin.y) / r.dir.y; 
    float tymax = (max.y - r.origin.y) / r.dir.y; 
 
    if (tymin > tymax)
    {
        float temp = tymin;
        tymin = tymax;
        tymax = temp;
    }
 
    if ((tmin > tymax) || (tymin > tmax)) 
        return false; 
 
    if (tymin > tmin) 
        tmin = tymin; 
 
    if (tymax < tmax) 
        tmax = tymax; 
 
    float tzmin = (min.z - r.origin.z) / r.dir.z; 
    float tzmax = (max.z - r.origin.z) / r.dir.z; 
 
    if (tzmin > tzmax) 
    {
        float temp = tzmin;
        tzmin = tzmax;
        tzmax = temp;
    }
 
    if ((tmin > tzmax) || (tzmin > tmax)) 
        return false; 
 
    if (tzmin > tmin) 
        tmin = tzmin; 
 
    if (tzmax < tmax) 
        tmax = tzmax; 
 
    return true; 
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
    float intersection_distance; // Output of TestRayOBBIntersection()
    glm::vec3 aabb_min(-1.0f, -1.0f, -1.0f); //Need to update
    glm::vec3 aabb_max( 1.0f,  1.0f,  1.0f); //Need to update

    aabb_min = vertices[0].Position;
    aabb_max = vertices[0].Position;

    //Should just be done once
    for (int i = 0; i < vertices.size(); i++)
    {
        glm::vec3 pos = vertices[i].Position;
        aabb_min = glm::vec3(glm::min(pos.x, aabb_min.x), glm::min(pos.y, aabb_min.y), glm::min(pos.z, aabb_min.z));
        aabb_max = glm::vec3(glm::max(pos.x, aabb_max.x), glm::max(pos.y, aabb_max.y), glm::max(pos.z, aabb_max.z));
    }

    ray.origin = glm::vec3(glm::inverse(model) * glm::vec4(ray.origin, 1.0f));
    ray.dir = glm::normalize(glm::vec3(glm::inverse(model) * glm::vec4(ray.dir, 0.0f)));

    if (TestRayOBBIntersection(ray, aabb_min, aabb_max))
    {
        std::cout << "INTERSECT\n"
                    << std::endl;
        return true;
    }
    else
    {
        std::cout << aabb_min.x << "," << aabb_min.y << "," << aabb_min.z << " || " << aabb_max.x << "," << aabb_max.y << "," << aabb_max.z << std::endl;
        return false;
    }
}
