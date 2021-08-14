#include "shader.h"

//Load files
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexString;
    std::string fragmentString;

    readFile(vertexPath,vertexString);
    readFile(fragmentPath, fragmentString);

    const char *vertexShader = vertexString.c_str();
    const char *fragmentShader = fragmentString.c_str();

    std::cout << vertexShader << "\n";

    if (vertexShader != "" && fragmentShader != "")
    {
        //Compile

        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexShader, NULL);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentShader, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        ID = glCreateProgram();

        std::cout << "Linked Shader Program " << ID << "\n";

        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);

        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
}

void Shader::MVP (glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
    setMat4("model", model);
    setMat4("view", view);
    setMat4("projection", projection);
}

void Shader::use ()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setVec3 (const std::string &name, glm::vec3 value) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::setMat4 (const std::string &name, glm::mat4 transform) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(transform));

}

int Shader::readFile (const char* path, std::string &output)
{
    std::ifstream file;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        file.open(path);
        std::stringstream fileStream;
        
        fileStream << file.rdbuf();
        file.close();

        output = fileStream.str();


        return 0;
    }
    catch (std::ifstream::failure e)
    {
        return 1;
    }
}