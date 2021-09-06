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
        Shader();

        void use();
        
        //const evaluated
        void setBool(const std::string &name, bool value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec3(const std::string &name, glm::vec3 value) const;
        void setMat4(const std::string &name, glm::mat4 matrix) const;

        int readFile (const char* path, std::string &output);
        void MVP(glm::mat4 model, glm::mat4 view, glm::mat4 project);
};

#endif