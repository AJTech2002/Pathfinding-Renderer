#ifndef SHADER
#define SHADER

#include "../common.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
        unsigned int ID;
        Shader(const char *vertexPath, const char *fragmentShaderPath);

        void use();
        
        //const evaluated
        void setBool(const std::string &name, bool value) const;
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, glm::mat4 matrix) const;

        int readFile (const char* path, std::string &output);
};

#endif