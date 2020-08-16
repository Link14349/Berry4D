#include "../include/object.h"

void Object::rotate(const Vector4 &r) {
    float A[4][4];
    rotation += r;
    rotationMatrix(rotation, A);
    auto rp = rawPoints.begin();
    for (auto point : points) {
        point->rotate(**rp, A);
        rp++;
    }
}