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
    auto it = rawNormals.begin();
    for (auto body : bodys) {
        auto va = *points[body->points[0]] - *points[body->points[1]],
             vb = *points[body->points[0]] - *points[body->points[2]],
             vc = *points[body->points[0]] - *points[body->points[3]];
        ::normal(*body->n, va, vb, vc);
        if (points[body->points[0]]->operator*(*body->n) < 0)
            body->n->operator*(-1);
        **(it++) = *body->n;
    }
}
