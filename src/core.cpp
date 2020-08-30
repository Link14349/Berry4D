#include "../include/core.h"
#include "../include/scene.h"
#include "../include/timestamp.h"

void Berry4D::use(Scene *s) {
    scene = s;
    scene->berry4d = this;
}

int Berry4D::render(void (*cb)()) {
    glfwMakeContextCurrent(win);
    float invh = 1 / height();
//    glPolygonMode(GL_FRONT, GL_LINE);
//    float x1 = -1, y1 = -1;
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
//    gluPerspective(2.1, 1, 0.1, 100);
    auto renderStart = getCurrentTime();
    while(!glfwWindowShouldClose(win)){
        glfwGetWindowSize(win, &w, &h);
        glMatrixMode(GL_PROJECTION);
        glClearColor (0.0, 0.0, 0.0, 0.0);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
        glDepthFunc(GL_LESS);
        glLoadIdentity();
        auto start = getCurrentTime();
        if (cb) cb();
        auto end = getCurrentTime();
        glfwSetWindowTitle(win, (title + " FPS: " + std::to_string(1000 / (float)(end - start))).c_str());
        scene->render();
        for (auto it = actions.begin(); it != actions.end(); ) {
            if (end - renderStart >= (*it)->st) {
                if (end - renderStart >= (*it)->ed) {
                    delete *it;
                    actions.erase(it++);
                    continue;
                }
                (*it)->action();
            }
            it++;
        }
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
