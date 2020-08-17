#include "../include/vec.h"
#include <cmath>

void rotationMatrix(float tx, float ty, float tz, float tw, float A[4][4]) {
    float sx = sin(tx), sy = sin(ty), sz = sin(tz), sw = sin(tw);
    float cx = cos(tx), cy = cos(ty), cz = cos(tz), cw = cos(tw);
    float xl = 1 / sqrt(1 + sx * sx), yl = 1 / sqrt(1 + sy * sy), zl = 1 / sqrt(1 + sz * sz), wl = 1 / sqrt(1 + sw * sw);
    sx *= xl, cx *= xl;
    sy *= yl, cy *= yl;
    sz *= zl, cz *= zl;
    sw *= wl, cw *= wl;
    float sxsy = sx * sy;
    float cxcy = cx * cy;
    float cxsy = cx * sy;
    float TMP1 = (((cy)) * (cz) + ((sy)) * (sz));
    float TMP2 = (((cy)) * (-sz) + ((sy)) * (-sz));
    float TMP12 = ((sx)) * (sz);
    float TMP13 = ((sx)) * (cz);
    float TMP3 = TMP12 + (sxsy + cxcy) * (sz);
    float TMP4 = TMP13 + (sxsy + cxcy) * (-sz);
    float TMP5 = (-sx) * (cy) + (-sxsy);
    float TMP6 = 2 * sxsy;
    float TMP7 = (-cxsy) + (-sxsy);
    float TMP8 = ((-cxsy) + (sx) * (cy));
    float TMP9 = sxsy + (-cxsy);
    float TMP10 = (sxsy + (-sx) * (cy));
    float TMP11 = ((cx)) * (cz);
    float TMP14 = TMP8 * (sz);
    float TMP15 = (cxcy + sxsy);
    float TMP16 = (((-sx) * (cy) + cxsy));
    A[0][0] = TMP1 * (cw) + TMP2 * (sw) - (((sy))) * (sw);
    A[0][1] = TMP1 * (-sw) + TMP2 * (cw) + (((sy))) * (sw);
    A[0][2] = TMP1 * (sw) + TMP2 * (-sw) + (((sy))) * (cw);
    A[0][3] = (((cy)) * (-sz) + ((sy)) * (cz));
    A[1][0] = ((TMP6) * (cz) + ((cx)) * (sz) + TMP10 * (sz)) * (cw) +
              ((TMP6) * (-sz) + TMP11 + (sxsy + (sx) * (cy)) * (sz)) * (sw) +
              ((TMP5)) * (-sw);
    A[1][1] = ((TMP6) * (cz) + ((cx)) * (sz) + TMP10 * (sz)) * (-sw) +
              ((TMP6) * (-sz) + TMP11 + TMP10 * (-sz)) * (cw) +
              ((TMP5)) * (sw);
    A[1][2] = ((TMP6) * (cz) + ((cx)) * (sz) + TMP10 * (sz)) * (sw) +
              ((TMP6) * (-sz) + TMP11 + TMP10 * (-sz)) * (-sw) +
              ((TMP5)) * (cw);
    A[1][3] = ((TMP6) * (-sz) + ((cx)) * (sz) + TMP10 * (cz));
    A[2][0] = ((TMP7) * (cz) + TMP12 + TMP14) * (cw) +
              ((TMP7) * (-sz) + TMP13 + TMP8 * (-sz)) * (sw) +
              (TMP15) * (-sw);
    A[2][1] = ((TMP7) * (cz) + TMP12 + TMP14) * (-sw) +
              ((TMP7) * (-sz) + TMP13 - TMP14) * (cw) +
              (TMP15) * (sw);
    A[2][2] = ((TMP7) * (cz) + TMP12 + TMP14) * (sw) +
              ((TMP7) * (-sz) + TMP13 - TMP14) * (-sw) +
              (TMP15) * (cw);
    A[2][3] = ((TMP7) * (-sz) + TMP12 + TMP8 * (cz));
    A[3][0] = ((TMP9) * (cz) + TMP3) * (cw) +
              ((TMP9) * (-sz) + TMP4) * (sw) +
              TMP16 * (-sw);
    A[3][1] = ((TMP9) * (cz) + TMP3) * (-sw) +
              ((TMP9) * (-sz) + TMP4) * (cw) +
              TMP16 * (sw);
    A[3][2] = ((TMP9) * (cz) + TMP3) * (sw) +
              ((TMP9) * (-sz) + TMP4) * (-sw) +
              TMP16 * (cw);
    A[3][3] = ((TMP9) * (-sz) + TMP12 + (sxsy + cxcy) * (cz));
//#define MP2(T) (T) * (T)
//    float xbasen = 1 / sqrt(MP2(A[0][0]) + MP2(A[1][0]) + MP2(A[2][0]) + MP2(A[3][0]));
//    float ybasen = 1 / sqrt(MP2(A[0][1]) + MP2(A[1][1]) + MP2(A[2][1]) + MP2(A[3][1]));
//    float zbasen = 1 / sqrt(MP2(A[0][2]) + MP2(A[1][2]) + MP2(A[2][2]) + MP2(A[3][2]));
//    float wbasen = 1 / sqrt(MP2(A[0][3]) + MP2(A[1][3]) + MP2(A[2][3]) + MP2(A[3][3]));
//    A[0][0] *= xbasen, A[1][0] *= xbasen, A[2][0] *= xbasen, A[3][0] *= xbasen;
//    A[0][1] *= ybasen, A[1][1] *= ybasen, A[2][1] *= ybasen, A[3][1] *= ybasen;
//    A[0][2] *= zbasen, A[1][2] *= zbasen, A[2][2] *= zbasen, A[3][2] *= zbasen;
//    A[0][3] *= wbasen, A[1][3] *= wbasen, A[2][3] *= wbasen, A[3][3] *= wbasen;
}

void rotationMatrix(const Vector4 &rotation, float A[4][4]) {
    rotationMatrix(rotation.x, rotation.y, rotation.z, rotation.w, A);
}

void Vector4::rotate(const Vector4 &raw, const float A[4][4]) {
//    auto l1 = raw.mod2();
    x = A[0][0] * raw.x + A[0][1] * raw.y + A[0][2] * raw.z + A[0][3] * raw.w;
    y = A[1][0] * raw.x + A[1][1] * raw.y + A[1][2] * raw.z + A[1][3] * raw.w;
    z = A[2][0] * raw.x + A[2][1] * raw.y + A[2][2] * raw.z + A[2][3] * raw.w;
    w = A[3][0] * raw.x + A[3][1] * raw.y + A[3][2] * raw.z + A[3][3] * raw.w;
//    auto l2 = mod2();
//    operator*=(sqrt(l1 / l2));
}

void Vector4::rotate(const float A[4][4]) {
//    auto l1 = mod2();
    float x_ = A[0][0] * x + A[0][1] * y + A[0][2] * z + A[0][3] * w;
    float y_ = A[1][0] * x + A[1][1] * y + A[1][2] * z + A[1][3] * w;
    float z_ = A[2][0] * x + A[2][1] * y + A[2][2] * z + A[2][3] * w;
    float w_ = A[3][0] * x + A[3][1] * y + A[3][2] * z + A[3][3] * w;
    x = x_;
    y = y_;
    z = z_;
    w = w_;
//    auto l2 = mod2();
//    operator*=(sqrt(l1 / l2));
}

void normal(Vector4 &target, const Vector4 &a, const Vector4 &b, const Vector4 &c) {
    target.x = (+(a.y) * (+(b.z) * (c.w) - (b.w) * (c.z)) - (a.z) * (+(b.y) * (c.w) - (b.w) * (c.y)) +
                (a.w) * (+(b.y) * (c.z) - (b.z) * (c.y)));
    target.y = -(+(a.x) * (+(b.z) * (c.w) - (b.w) * (c.z)) - (a.z) * (+(b.x) * (c.w) - (b.w) * (c.x)) +
                 (a.w) * (+(b.x) * (c.z) - (b.z) * (c.x)));
    target.z = +(+(a.x) * (+(b.y) * (c.w) - (b.w) * (c.y)) - (a.y) * (+(b.x) * (c.w) - (b.w) * (c.x)) +
                 (a.w) * (+(b.x) * (c.y) - (b.y) * (c.x)));
    target.w = -(+(a.x) * (+(b.y) * (c.z) - (b.z) * (c.y)) - (a.y) * (+(b.x) * (c.z) - (b.z) * (c.x)) +
                 (a.z) * (+(b.x) * (c.y) - (b.y) * (c.x)));
}
void normal3D(Vector4 &target, const Vector4 &a, const Vector4 &b, const Vector4 &c) {
    target.x = ( + (a.y) * (b.z) - (a.z) * (b.y));
    target.y = -( + (a.x) * (b.z) - (a.z) * (b.x));
    target.z = ( + (a.x) * (b.y) - (a.y) * (b.x));
    target.w = 0;
}