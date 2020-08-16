#include "../include/core.h"
#include "../include/scene.h"
#include "../include/timestamp.h"

void Berry4D::use(Scene *s) {
    scene = s;
}

int Berry4D::render(void (*cb)()) {
    glfwMakeContextCurrent(win);
    float invh = 1 / height();
//    float x1 = -1, y1 = -1;
    while(!glfwWindowShouldClose(win)){
        glfwGetWindowSize(win, &w, &h);
        glClearColor (0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        auto start = getCurrentTime();
        scene->render();
        if (cb) cb();
        auto end = getCurrentTime();
        glfwSetWindowTitle(win, (title + " FPS: " + std::to_string(1000 / (float)(end - start))).c_str());
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
