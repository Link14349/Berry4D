#include "include/core.h"
#include "include/scene.h"
#include "include/camera.h"
#include "include/cube.h"

Cube cube(1, 1, 1, 1);
#define V 0.03
void cb() {
    cube.rotate(Vector4(V, V, V, 0));
}

int main() {
    Berry4D berry4D("Berry4D");
    Scene scene;
    Camera camera;
    camera.position.w = -2;
    berry4D.use(&scene);
    scene.use(&camera);
    scene.push(&cube);
    berry4D.render(cb);
    return 0;
}
