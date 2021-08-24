#ifndef RAY
#define RAY

#include "../common.h"

struct Ray
{
    glm::vec3 origin;
    glm::vec3 dir;
    float maxDist;
};

struct RayHit
{
    glm::vec3 hitPoint;
};

#endif