#ifndef MESH
#define MESH
#include "../common.h"
#include "shader.h"
#include "camera.h"
#include "ray.h"
#include "vertex.h"

class Mesh
{
    private:
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
        glm::vec3 worldCoordinate(glm::vec3 modelCoordinate);
        Shader *linkedShader;
        bool doesIntersectTriangle(Vertex *v1, Vertex *v2, Vertex *v3, Ray &ray);
        float PointInOrOn(glm::vec3 p1, glm::vec3 p2, glm::vec3 start, glm::vec3 end);
        bool PointInTriangle(glm::vec3 px, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2);
        glm::vec3 IntersectPlane(Ray &ray, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2);

    public:
        glm::vec3 tint = glm::vec3(1.0f); //Todo: move to material object
        glm::mat4 model = glm::mat4(1.0f);
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        bool rayDoesIntersect(Ray &ray);

        void draw(VCamera* sceneCamera);
        void init();

        Mesh(Shader *meshShader, std::vector<Vertex> vertices, std::vector<unsigned int> indices);
};

#endif