#ifndef BERRY4D_OBJECT_H
#define BERRY4D_OBJECT_H

#include <vector>
#include <list>
#include "vec.h"

class Object {
    friend class Camera;
public:
    struct Body {
        Body(Vector4* _n, unsigned a, unsigned b, unsigned c, unsigned d) : n(_n) {
            points[0] = a;
            points[1] = b;
            points[2] = c;
            points[3] = d;
        }
        Vector4* n;
        unsigned points[4];
    };
    void rotate(const Vector4&);
    Vector4 position;
protected:
    void normal();
    Vector4 rotation;
    std::vector<Vector4*> points;
    std::list<Vector4*> rawPoints;
    std::list<Vector4*> rawNormals;
    std::vector<Body*> bodys;
};


#endif //BERRY4D_OBJECT_H
