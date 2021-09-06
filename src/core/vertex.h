#ifndef VERTEX
#define VERTEX
#include "../common.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 PrevPos;
    bool locked;
};

struct Stick {
    int a;
    int b;
    float length;
    Stick (int _a, int _b, float _length)
    {
        a = _a;
        b = _b;
        length = _length;
    }
};


#endif