#ifndef BERRY4D_SCENE_H
#define BERRY4D_SCENE_H

#include <list>
#include "object.h"
#include "camera.h"
#include "light.h"

class Berry4D;
class Scene {
    friend class Camera;
    friend class Berry4D;
public:
    Scene() : camera(nullptr) { }
    Scene(Camera* c) : camera(c) { c->scene = this; }
    void render() { camera->render(); }
    void use(Camera* c) { (camera = c)->scene = this; }
    void push(Object* object) { objects.push_back(object); }
    void push(Light* light) { lights.push_back(light); }
    Color ambientLightColor;
private:
    Camera* camera;
    Berry4D* berry4d;
    std::list<Object*> objects;
    std::list<Light*> lights;
};


#endif //BERRY4D_SCENE_H
