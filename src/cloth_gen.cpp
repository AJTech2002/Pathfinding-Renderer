#include "cloth_gen.h"

int index (int i , int c, int sizeY)
{
    return i * sizeY + c;
}

bool validIndex (int i, int c, int sizeX, int sizeY)
{
    if (i * c > sizeX * sizeY - 1)
        return false;
    
    if (i < 0 || c < 0) return false;

    if (i > sizeX -1 || c > sizeY -1)
        return false;
    
}

void generate_cloth_mesh (int sizeX, int sizeY, float gridWidth, glm::vec3 topLeft, 
                            Shader* clothShader, std::vector<Vertex>& verts, 
                            std::vector<unsigned int>& indices, std::vector<Stick>& sticks,
                            glm::mat4 transformVert
                        )
{

    for (int i = 0; i < sizeX; i++)
    {
        for (int c = 0; c < sizeY; c++) {
            Vertex v;
            //((float)i*(float)c*40.0f)/100.0f

            //Allow for matrix transformation
            glm::vec3 expectedPosition = topLeft + glm::vec3(i * gridWidth, -c * gridWidth, 0.0f);
            v.Position = glm::vec3(transformVert * glm::vec4(expectedPosition, 1.0f));

            v.PrevPos = v.Position;
            v.Normal = glm::vec3(0.0f, 0.0f, -1.0f);

            // if ((i == 0 && c < 1) || (i == sizeX-2 && c < 1) )
            //     v.locked = true;
            // else
            //     v.locked = false;

            //Stick Generation from (https://github.com/bailus/Cloth/blob/master/Cloth.cpp)
            bool
                leftCol = (i == 0),
                rightCol = (i == sizeX - 1),
                topRow = (c == 0),
                topRows = (c <= 1),
                leftCols = (i == 0 || i == 1);

            if (!topRow)
                sticks.push_back(Stick(index(i, c, sizeY), index(i, c - 1, sizeY), gridWidth));
            
            // if (!topRows)
            //     sticks.push_back(Stick(index(i, c, sizeY), index(i, c - 2, sizeY), gridWidth));
            
            if (!leftCol)
                sticks.push_back(Stick(index(i, c, sizeY), index(i-1, c, sizeY), gridWidth));
            
            // if (!leftCols)
            //     sticks.push_back(Stick(index(i, c, sizeY), index(i-2, c, sizeY), gridWidth));
            
            // if (!rightCol)
            //     sticks.push_back(Stick(index(i, c, sizeY), index(i+1, c, sizeY), gridWidth));
            // if (!topRow && !leftCol)
            //     sticks.push_back(Stick(index(i, c, sizeY), index(i+1, c+1, sizeY), gridWidth));
            
            // if (!topRow && !rightCol)
            //     sticks.push_back(Stick(index(i, c, sizeY), index(i-1, c-1, sizeY), gridWidth));

            verts.push_back(v);

            // if (index(i+1,c,sizeY) < (sizeX*sizeY)-1 && index(i,c+1,sizeY) < (sizeX*sizeY)-1 && i+1 < sizeX-1 && c+1 < sizeY-1)
            if (i < sizeX - 2 && c < sizeY - 2)
            {
                //Mesh Indices
                indices.push_back(index(i, c, sizeY));
                indices.push_back(index(i, c + 1, sizeY));
                indices.push_back(index(i + 1, c, sizeY));

                indices.push_back(index(i, c + 1, sizeY));
                indices.push_back(index(i + 1, c + 1, sizeY));
                indices.push_back(index(i + 1, c, sizeY));
            }
        }
    }

    for (int i = 0; i < sticks.size(); i++)
    {
        sticks[i].length = glm::distance(
            verts[sticks[i].a].Position,
            verts[sticks[i].b].Position);
    }
}


//https://www.ics.uci.edu/~shz/courses/cs114/docs/proj3/index.html (TODO Use this to implement better physics!)
void simulate (Mesh* mesh, Sphere* sphere)
{
    //Move Downd
    float friction = 1.0f;
    int collisionPoints = 0;
    for (int i = 0; i < mesh->vertices.size(); i++)
    {
        if (mesh->vertices[i].locked)
            continue;

        glm::vec3 posBefore = mesh->vertices[i].Position;
        
        //Compound Speed (0.5 to emulate drag)
        mesh->vertices[i].Position += (mesh->vertices[i].Position - mesh->vertices[i].PrevPos)*0.5f;
        //float wind = glm::sin(mesh->vertices[i].Position.x*glfwGetTime()*0.3f)*0.005f;
        mesh->vertices[i].Position += glm::vec3(0.0f, -0.06f*friction, 0.0f);
        
        //Try Collisions Here
        glm::vec3 sphereColDir = mesh->vertices[i].Position - sphere->center;
        float distance = glm::length(sphereColDir);

        if (distance < sphere->radius) {
            collisionPoints += 1;
            friction = (1.0f - (float)collisionPoints / (float)mesh->vertices.size());
            mesh->vertices[i].Position += glm::normalize(sphereColDir) * (sphere->radius - distance);
        }
        mesh->vertices[i].PrevPos = posBefore;
    }

    //Collisions

    // Create Stability through iterations ( > n = better)
    for (int n = 0; n < 10; n++) {
        for (int i = 0; i < mesh->sticks.size(); i++)
        {
            
            Vertex *aV = &mesh->vertices[mesh->sticks[i].a];
            Vertex *bV = &mesh->vertices[mesh->sticks[i].b];
            
            glm::vec3 v = aV->Position - bV->Position;

            float pow = 0.8f;
            if (aV->locked || bV->locked)
                pow = 0.9f;

            v *= ((1.0f - mesh->sticks[i].length/glm::length(v)) * pow);

            if (!aV->locked)
                aV->Position += glm::vec3(-v.x, -v.y, -v.z);
            if (!bV->locked)
                bV->Position += v;
        }
    }
}