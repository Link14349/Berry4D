#include "../include/core.h"
#include "../include/scene.h"
#include "../include/timestamp.h"

void Berry4D::use(Scene *s) {
    scene = s;
}

static void changeSize(GLsizei w, GLsizei h)
{
    if(h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(w <= h)
    {
        glOrtho(0.0f, 300.0f, 0.0f, 300.0f * h/w, 1.0f, -1.0f);
    }else
    {
        glOrtho(0.0f, 300.0f * w/h, 0.0f, 300.0f, 1.0f, -1.0f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int Berry4D::render(void (*cb)()) {
    glfwMakeContextCurrent(win);
    float invh = 1 / height();
//    glPolygonMode(GL_FRONT, GL_LINE);
//    float x1 = -1, y1 = -1;
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(win)){
        glfwGetWindowSize(win, &w, &h);
        glMatrixMode(GL_PROJECTION);
        glClearColor (0.0, 0.0, 0.0, 0.0);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);
        glLoadIdentity();
        auto start = getCurrentTime();
        scene->render();
//        {
//            glBegin(GL_TRIANGLES);
//            GLfloat a[] = {
//                    0, 0.5, 0,
//                    .5, -0.5, 0,
//                    -0.5, -0.5, 0,
//                    0, .25, 0.5,
//                    .5, -.25, -0.5,
//                    -0.5, -.25, -0.5,
//            };
//            glColor3f(0.9, 0.9, 0.9);
//            glVertex3fv(a + 9);
//            glVertex3fv(a + 12);
//            glVertex3fv(a + 15);
//            glColor3f(0.5, 0.5, 0.5);
//            glVertex3fv(a);
//            glVertex3fv(a + 3);
//            glVertex3fv(a + 6);
//            glEnd();
//        }
        if (cb) cb();
        auto end = getCurrentTime();
        glfwSetWindowTitle(win, (title + " FPS: " + std::to_string(1000 / (float)(end - start))).c_str());
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
