#ifndef BERRY4D_CORE_H
#define BERRY4D_CORE_H


#include <string>
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>

class Scene;
class Berry4D {
public:
    Berry4D(const std::string& title, int w = 800, int h = 800) : scene(nullptr), win(nullptr), title(title), w(w), h(h) {
        if(!glfwInit())
            exit(-1);
        win = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
        if(!win)
        {
            glfwTerminate();
            exit(-1);
        }
    }
    int render(void(*)() = nullptr);
    float width() { return w; }
    float height() { return h; }
    void setKeyEvent(void (*cb)(GLFWwindow*, int, int, int, int)) { glfwSetKeyCallback(win, cb); }
    void use(Scene* s);
private:
    int w, h;
    GLFWwindow* win;
    Scene* scene;
    std::string title;
};


#endif //BERRY4D_CORE_H
