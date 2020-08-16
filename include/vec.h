#ifndef BERRY4D_VEC_H
#define BERRY4D_VEC_H

#include <cmath>

class Vector4 {
public:
    Vector4(float a = 0, float b = 0, float c = 0, float d = 0) : x(a), y(b), z(c), w(d) {}

    Vector4(const Vector4 &vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}

    Vector4 &operator=(const Vector4 &vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = vec.w;
        return *this;
    }

#define MATH_VEC_OP(NAME, OP) NAME OP vec.NAME

    Vector4 operator+(const Vector4 &vec) const { return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w); }

    Vector4 &operator+=(const Vector4 &vec) {
        MATH_VEC_OP(x, +=);
        MATH_VEC_OP(y, +=);
        MATH_VEC_OP(z, +=);
        MATH_VEC_OP(w, +=);
        return *this;
    }

    Vector4 &operator-=(const Vector4 &vec) {
        MATH_VEC_OP(x, -=);
        MATH_VEC_OP(y, -=);
        MATH_VEC_OP(z, -=);
        MATH_VEC_OP(w, -=);
        return *this;
    }

    void inverse() {
        x = -x;
        y = -y;
        z = -z;
        w = -w;
    }

    Vector4 operator-(const Vector4 &vec) const { return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w); }

    Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }

    // 点积
    float operator*(const Vector4 &vec) const {
        return MATH_VEC_OP(x, *) + MATH_VEC_OP(y, *) + MATH_VEC_OP(z, *) + MATH_VEC_OP(w, *);
    }
    Vector4& operator*=(const float a) {
        x *= a;
        y *= a;
        z *= a;
        w *= a;
        return *this;
    }
    float mod2() const { return x * x + y * y + z * z + w * w; }
    float mod() const { return sqrt(x * x + y * y + z * z + w * w); }
    void rotate(const float[4][4]);
    void rotate(const Vector4&, const float[4][4]);
    float x, y, z, w;
};


void rotationMatrix(float, float, float, float, float[4][4]);
void rotationMatrix(const Vector4& rotation, float A[4][4]);


#endif //BERRY4D_VEC_H
