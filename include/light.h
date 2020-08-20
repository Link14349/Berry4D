#ifndef BERRY4D_LIGHT_H
#define BERRY4D_LIGHT_H

#include "vec.h"

class Light {
public:
    Light(float r, float g, float b, const Vector4& pos) : position(pos), color(r, g, b) { }
    Color color;
    Vector4 position;
};
class Material {
public:
    Material(Color c, float ka, float kd, float ks, float power)
            : color(c),
              ka(ka), kd(kd), ks(ks), power(power),
              ra(c * ka), rd(c * kd), rs(c * ks)
    { }
    Color color;// 表面颜色
    float ka, kd, ks, power;// 环境光反射系数, 散射光反射系数, 镜面反射光反射系数, 镜面反射指数
    Color ra, rd, rs;// 环境光, 散射光, 镜面反射光颜色
};
#define AMIBIENT 0.3


#endif //BERRY4D_LIGHT_H
