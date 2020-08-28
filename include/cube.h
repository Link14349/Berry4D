#ifndef BERRY4D_CUBE_H
#define BERRY4D_CUBE_H

#include <iostream>
#include "object.h"

class Cube : public Object {
public:
    Cube(float x = 1, float y = 1, float z = 1, float w = 1) {
        x *= .5, y *= .5, z *= .5, w *= .5;
#define CUBE_PUSH_POINT(a, b, c, d) { points.push_back(new Vector4(a x, b y, c z, d w)); rawPoints.push_back(new Vector4(a x, b y, c z, d w)); }
#define CUBE_GET_POINT_ID(x, y, z, w) x | (y << 1) | (z << 2) | (w << 3)
        CUBE_PUSH_POINT( , , , )
        CUBE_PUSH_POINT(-, , , )
        CUBE_PUSH_POINT( ,-, , )
        CUBE_PUSH_POINT(-,-, , )
        CUBE_PUSH_POINT( , ,-, )
        CUBE_PUSH_POINT(-, ,-, )
        CUBE_PUSH_POINT( ,-,-, )
        CUBE_PUSH_POINT(-,-,-, )
        CUBE_PUSH_POINT( , , ,-)
        CUBE_PUSH_POINT(-, , ,-)
        CUBE_PUSH_POINT( ,-, ,-)
        CUBE_PUSH_POINT(-,-, ,-)
        CUBE_PUSH_POINT( , ,-,-)
        CUBE_PUSH_POINT(-, ,-,-)
        CUBE_PUSH_POINT( ,-,-,-)
        CUBE_PUSH_POINT(-,-,-,-)
        for (char i = 0; i < 16; i++) {
            bool w = (i >> 3) & 1;
            bool z = (i >> 2) & 1;
            bool y = (i >> 1) & 1;
            bool x = i & 1;
#define CUBE_PUSH_BODY(a, b, c, d, e, f, g, h, i, j, k, l) bodys.push_back(new Object::Body(new Vector4, CUBE_GET_POINT_ID(x, y, z, w), CUBE_GET_POINT_ID(a x, b y, c z, d w), CUBE_GET_POINT_ID(e x, f y, g z, h w), CUBE_GET_POINT_ID(i x, j y, k z, l w))); rawNormals.push_back(new Vector4);
            CUBE_PUSH_BODY
            (! ,  ,  ,  ,
               ,! ,  ,  ,
               ,  ,! ,  )
            CUBE_PUSH_BODY
            (  ,! ,  ,  ,
               ,  ,! ,  ,
               ,  ,  ,! )
            CUBE_PUSH_BODY
            (  ,  ,! ,  ,
               ,  ,  ,! ,
             ! ,  ,  ,  )
            CUBE_PUSH_BODY
            (  ,  ,  ,! ,
             ! ,  ,  ,  ,
               ,! ,  ,  )
        }
        radius = sqrt(x * x + y * y + z * z + w * w);
        normal();
    }
private:
};


#endif //BERRY4D_CUBE_H
