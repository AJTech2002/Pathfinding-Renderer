#include "../common.h"
#include "shader.h"
#include "camera.h"
#include "mesh.h"

class Model 
{
    public:
        Model (char* path, Shader* meshShader)
        {

        }
        void draw(VCamera *cam);
        
    private:
        std::vector<Mesh> meshes;
        std::string directory;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        
}