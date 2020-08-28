#include <iostream>
#include <cmath>
#include "include/core.h"
#include "include/scene.h"
#include "include/camera.h"
#include "include/cube.h"
#include "include/be4dLoader.h"

Camera camera;
Object* spaceShip;
void cb() {
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
    // 初始化引擎
    Berry4D berry4D("Berry4D");
    Scene scene;
    berry4D.use(&scene);
    scene.use(&camera);
    glfwSetKeyCallback(berry4D.glfwin(), keyboardFunc);

    // 导入模型
    uint32_t len;
    char* content = readFileCPTR("spaceShip.be4d", len);
    be4dLoader loader((unsigned char*)content, len);
    spaceShip = loader.load();
    delete[] content;

    // 设置物体位置
    camera.position.w = -2;

    // 添加物体
    scene.push(spaceShip);

    berry4D.render(cb);// 渲染

    // 结束，清理
    delete spaceShip;
    return 0;
}