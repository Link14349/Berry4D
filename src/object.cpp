#include "../include/object.h"


void Object::rotate(const Vector4 &rotation) {
    float A[4][4];
    rotationMatrix(rotation, A);
    for (auto point : points) {
        auto l1 = point->mod2();
        point->rotate(A);
        auto l2 = point->mod2();
        point->operator*=(sqrt(l1 / l2));
    }
}