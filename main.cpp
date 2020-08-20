#include <iostream>
#include <cmath>
#include "include/core.h"
#include "include/scene.h"
#include "include/camera.h"
#include "include/cube.h"
#include "include/be4dLoader.h"

Cube cube(1, 1, 1, 0.01);
Camera camera;
Object* obj;
#define V 0.02
void cb() {
    obj->rotate(Vector4(0, 0, 0, V));
    cube.rotate(Vector4(V, V, V, V));
//    cube.position.w += 0.01;
}
void keyboardFunc(GLFWwindow* win, int key, int scancode, int action, int mods)
{
    switch(key) {
        case GLFW_KEY_UP:
            camera.position.w += 0.1;
            break;
        case GLFW_KEY_DOWN:
            camera.position.w -= 0.1;
            break;
        case GLFW_KEY_LEFT:
            camera.position.x -= 0.1;
            break;
        case GLFW_KEY_RIGHT:
            camera.position.x += 0.1;
            break;
    }
}

int main() {
//    cube.rotate(Vector4(M_PI / 4, M_PI / 4));
    Light light(1, .3, .2, Vector4(0, 0, 0, 2));
    Berry4D berry4D("Berry4D");
    Scene scene;
    uint32_t len;
    char* content = readFileCPTR("link.be4d", len);
    be4dLoader loader((unsigned char*)content, len);
    obj = loader.load();
    obj->scale(0.01);
    obj->position.w = 10;
    obj->position.y = -4;
    cube.position.w = 1;
    camera.position.w = -2;
    scene.ambientLightColor = Color(1, 1,1);
    scene.push(&light);
//    scene.push(obj);
    glfwSetKeyCallback(berry4D.glfwin(), keyboardFunc);
    berry4D.use(&scene);
    scene.use(&camera);
    scene.push(&cube);
    berry4D.render(cb);
    delete obj;
    delete content;
    return 0;
}