#ifndef BERRY4D_SCENE_H
#define BERRY4D_SCENE_H

#include <list>
#include "object.h"
#include "camera.h"

class Scene {
    friend class Camera;
public:
    Scene() : camera(nullptr) { }
    Scene(Camera* c) : camera(c) { c->scene = this; }
    void render() { camera->render(); }
    void use(Camera* c) { (camera = c)->scene = this; }
    void push(Object* object) { objects.push_back(object); }
private:
    Camera* camera;
    std::list<Object*> objects;
};


#endif //BERRY4D_SCENE_H
