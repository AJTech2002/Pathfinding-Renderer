#ifndef MODEL
#define MODEL
#include "../common.h"
#include "shader.h"
#include "camera.h"
#include "mesh.h"
#include "vertex.h"

class Model 
{
    public:
        Model (char* path, Shader* meshShader)
        {
            linkedShader = meshShader;
            loadModel(path);
        }
        std::vector<Mesh> meshes;
        void draw(VCamera *cam);
        bool didIntersectAnyMeshes(Ray &ray);
        Shader *linkedShader;
        
    private:
        
        std::string directory;
        
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

};
#endif