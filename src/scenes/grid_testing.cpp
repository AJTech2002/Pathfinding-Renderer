
#ifdef SCENE_GRID_TESTING

void onUpdate()
{
    //Game Logic & Scene Draw
    scene.drawScene();
}

void initScene ()
{
    Shader shader("C:/Users/Ajay/Desktop/Pathfinding-Renderer/src/shaders/vertex.glsl", "C:/Users/Ajay/Desktop/Pathfinding-Renderer/src/shaders/fragment.glsl");

    scene.sceneShaders.push_back(shader);

    Model capsuleModel("C:/Users/Ajay/Desktop/Pathfinding-Renderer/primitives/Cube.fbx", &scene.sceneShaders[0]);

    Light directionalLight;
    
    VCamera camera;

    scene.setupScene(directionalLight, camera);

    capsuleModel.meshes[0].tint = glm::vec3(107.0 / 256.0f, 190.0 / 256.0f, 242.0 / 256.0f);
    capsuleModel.meshes[0].model = glm::scale(capsuleModel.meshes[0].model, glm::vec3(0.3f, 1.5f, 2.0f));
    scene.addSceneObject(capsuleModel);
    
    camera.projection = glm::perspective(glm::radians(60.0f), 800.0f / 800.0f, 0.1f, 1000.0f);
    glLineWidth(2.0f);
}

#endif