#include "model.h"

void Model::draw(VCamera *cam)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw(cam);
}

bool Model::didIntersectAnyMeshes(Ray &ray, RayHit &hit)
{

    for (int i = 0; i < meshes.size(); i++)
        if (meshes[i].rayDoesIntersect(ray, hit))
            return true;

    return false;
}

//Reason for nodes is to keep parent child relationships (not just get the meshes)
void Model::loadModel (std::string path)
{
    Assimp::Importer import; //ASSIMP Importer

    //Triangulate ensures that vertex format is triangles
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    
    directory = path.substr(0, path.find_last_of('/'));
    
    //If nothing went wrong
    processNode(scene->mRootNode, scene);
}

//Scene -> Nodes -> Meshes (Recursive)
void Model::processNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    //Recursive step (go down the node)
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    //Final step
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        vertex.Position.x = mesh->mVertices[i].x;
        vertex.Position.y = mesh->mVertices[i].y;
        vertex.Position.z = mesh->mVertices[i].z;

        vertex.Normal.x = mesh->mNormals[i].x;
        vertex.Normal.y = mesh->mNormals[i].y;
        vertex.Normal.z = mesh->mNormals[i].z;

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh(linkedShader, vertices, indices);
}
