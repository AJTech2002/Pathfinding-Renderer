#ifndef CLOTH
#define CLOTH
#include "common.h"
#include "core.h"
#include "core/sphere.h"

void generate_cloth_mesh(int sizeX, int sizeY, float gridWidth, glm::vec3 topLeft,
                         Shader *clothShader, std::vector<Vertex> &verts,
                         std::vector<unsigned int> &indices, std::vector<Stick> &sticks, glm::mat4 transformVert);

void simulate(Mesh *mesh, Sphere* sphere);
#endif