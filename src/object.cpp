#include "../include/object.h"

void Object::rotate(const Vector4 &r) {
    float A[4][4];
    // 这里之所以是算总转动，不直接乘变换矩阵，是因为四维变换中对于变换矩阵值的误差相当敏感，再加上旋转往往是会进行很多次的，再将这一误差放大，就会令物体出现变形
    rotation += r;
    rotationMatrix(rotation, A);
    auto rp = rawPoints.begin();
    for (auto point : points) {
        point->rotate(**rp, A);
        rp++;
    }
    // 计算法向量
    auto rn = rawNormals.begin();
    for (auto body : bodys) {
        body->n->rotate(**rn, A);
        rn++;
    }
}

void Object::normal() {
    for (auto body : bodys) {
        auto va = body->points[0] - body->points[1], vb = body->points[0] - body->points[2], vc = body->points[0] - body->points[3];
        ::normal(*body->n, va, vb, vc);
    }
}
