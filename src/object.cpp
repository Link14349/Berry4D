#include "../include/object.h"


void Object::rotate(const Vector4 &rotation) {
    float A[4][4];
    rotationMatrix(rotation, A);
    for (auto point : points) point->rotate(A);
}