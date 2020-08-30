#include <iostream>
#include <cmath>
#include "include/core.h"
#include "include/scene.h"
#include "include/camera.h"
#include "include/cube.h"
#include "include/be4dLoader.h"

Camera camera;
Cube spaceShip(5, 1, 1, 0.001f);
Object* ring;
#define V .001f
void cb() {
    ring->rotate(Vector4(V, V, V, V));
}
void keyboardFunc(GLFWwindow* win, int key, int scancode, int action, int mods)
{
    switch(key) {
//        case GLFW_KEY_UP:
//            camera.position.w += 0.4;
//            break;
//        case GLFW_KEY_DOWN:
//            camera.position.w -= 0.4;
//            break;
//        case GLFW_KEY_LEFT:
//            camera.position.x -= 0.4;
//            break;
//        case GLFW_KEY_RIGHT:
//            camera.position.x += 0.4;
//            break;
        case GLFW_KEY_A:
            camera.rotation.y -= 0.1;
            break;
        case GLFW_KEY_D:
            camera.rotation.y += 0.1;
            break;
        case GLFW_KEY_S:
            camera.rotation.x += 0.1;
            break;
        case GLFW_KEY_W:
            camera.rotation.x -= 0.1;
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
    // 魔戒模型
    uint32_t len;
    char* content = readFileCPTR("ring.be4d", len);
    be4dLoader loader((unsigned char*)content, len);
    ring = loader.load(true);
    delete[] content;
    // 调整魔戒的方向以及宽度等信息
    ring->scale(Vector4(.5f, .5f, .5f, 1000));

    // 设置物体位置
    camera.position.x = -4;
    camera.position.w = -2;
    camera.rotation.y = M_PI * .125f;
    ring->position.x = -30;

    // 添加物体
    scene.push(&spaceShip);
    scene.push(ring);

    // 动画设置
    berry4D.action(0, 200000, []() {
        if (spaceShip.position.x > -10) spaceShip.position.x -= 0.01;
    });
    berry4D.action(500, 200000, []() {
        if (camera.rotation.y > -M_PI * .125f) camera.rotation.y -= 0.001;
    });
    berry4D.action(10000, 16000, []() {
        camera.position.x -= 0.005;
        camera.position.w += 0.005;
    });
    berry4D.action(20000, 50000, []() {
        if (camera.position.w < 0) camera.position.w += 0.005;
        if (camera.rotation.y > -M_PI * .125f) camera.rotation.y -= 0.001;
        if (camera.position.x > -4) camera.position.x -= 0.005;
    });

    berry4D.render(cb);// 渲染

    // 结束，清理
    delete ring;
    return 0;
}