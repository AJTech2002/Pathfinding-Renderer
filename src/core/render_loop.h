#include "../common.h"
#include "camera.h"
#include "light.h"
#include "scene.h"

void renderLoop(GLFWwindow* window);
void processInput(GLFWwindow *window, Scene *scene, VCamera *camera);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);