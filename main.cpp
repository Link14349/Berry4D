#include <iostream>
#include <cmath>
#include "include/core.h"
#include "include/scene.h"
#include "include/camera.h"
#include "include/cube.h"
#include "include/be4dLoader.h"

Cube cube(1, 1, 1, 1);
Camera camera;
Object* obj;
#define V 0.02
void cb() {
    obj->rotate(Vector4(0, V, 0, 0));
    cube.rotate(Vector4(V, V, V, V));
//    cube.position.w += 0.01;
}
void keyboardFunc(GLFWwindow* win, int key, int scancode, int action, int mods)
{
    switch(key) {
        case GLFW_KEY_UP:
            camera.position.w += 0.4;
            break;
        case GLFW_KEY_DOWN:
            camera.position.w -= 0.4;
            break;
        case GLFW_KEY_LEFT:
            camera.position.x -= 0.4;
            break;
        case GLFW_KEY_RIGHT:
            camera.position.x += 0.4;
            break;
        case GLFW_KEY_A:
            camera.rotation.y -= 0.1;
            break;
        case GLFW_KEY_D:
            camera.rotation.y += 0.1;
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
    delete[] content;
    content = readFileCPTR("cube.be4d", len);
    loader.reload((unsigned char*)content, len);
    auto obj2 = loader.load();
    obj2->position.w = -1;
    delete[] content;
    obj->position.w = 10;
    obj->position.y = -4;
    cube.position.w = 1;
    camera.position.w = -2;
    scene.ambientLightColor = Color(1, 1,1);
    scene.push(&light);
    glfwSetKeyCallback(berry4D.glfwin(), keyboardFunc);
    berry4D.use(&scene);
    scene.use(&camera);
//    scene.push(&cube);
    scene.push(obj);
//    scene.push(obj2);
    berry4D.render(cb);
    delete obj;
    return 0;
}