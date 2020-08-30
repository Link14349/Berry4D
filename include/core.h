#ifndef BERRY4D_CORE_H
#define BERRY4D_CORE_H


#include <string>
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
#include <list>

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
    void action(uint64_t st, uint64_t ed, void (*cb)()) {
        actions.push_back(new TimeAction(st, ed, cb));
    }
    GLFWwindow* glfwin() { return win; }
private:
    int w, h;
    GLFWwindow* win;
    Scene* scene;
    std::string title;
    struct TimeAction {
        TimeAction(uint64_t s, uint64_t e, void (*act)()) : st(s), ed(e), action(act) {}
        uint64_t st;
        uint64_t ed;
        void (*action)();
    };
    std::list<TimeAction*> actions;// 因为暂时time actions不多所以就用朴素方法，list存储，for循环全部遍历来判断是否触发action
};


#endif //BERRY4D_CORE_H
