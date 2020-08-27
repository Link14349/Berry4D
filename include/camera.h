#ifndef BERRY4D_CAMERA_H
#define BERRY4D_CAMERA_H

#include "vec.h"
#include "object.h"


class Scene;
class Camera {
    friend class Scene;
public:
    Camera() : position(), rotation() {}
    void render();
    Vector4 position;
    Vector4 rotation;
private:
    float TAN_hfov_x = 1.732;
    float TAN_hfov_y = 1.732;
    float TAN_hfov_z = 1.732;
    float iTAN_hfov_x = 1 / TAN_hfov_x;
    float iTAN_hfov_y = 1 / TAN_hfov_y;
    float iTAN_hfov_z = 1 / TAN_hfov_z;
    Scene* scene;
    float A[4][4];
};


#endif //BERRY4D_CAMERA_H
