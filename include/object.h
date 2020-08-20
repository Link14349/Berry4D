#ifndef BERRY4D_OBJECT_H
#define BERRY4D_OBJECT_H

#include <vector>
#include <list>
#include "vec.h"
#include "light.h"

class Object {
    friend class Camera;
    friend class be4dLoader;
public:
    struct Body {
        Body(Vector4* _n, unsigned a, unsigned b, unsigned c, unsigned d, float R = .5, float G = .5, float B = .5) : n(_n), material(new Material(Color(.1, .7, .0), .7, .8, 1, 2)) {
            points[0] = a;
            points[1] = b;
            points[2] = c;
            points[3] = d;
            color[0] = R;
            color[1] = G;
            color[2] = B;
        }
        ~Body() {
            delete n;
            delete material;
        }
        Vector4* n;
        Material* material;
        float color[3];
        unsigned points[4];
    };
    void rotate(const Vector4&);
    void scale(float k) {
        for (auto point : points) point->operator*(k);
        for (auto point : rawPoints) point->operator*(k);
    }
    Vector4 position;
    ~Object() {
        for (auto point : points) delete point;
        for (auto point : rawPoints) delete point;
        for (auto point : rawNormals) delete point;
        for (auto body : bodys) delete body;
    }
protected:
    void normal();
    Vector4 rotation;
    std::vector<Vector4*> points;
    std::list<Vector4*> rawPoints;
    std::list<Vector4*> rawNormals;
    std::vector<Body*> bodys;
};


#endif //BERRY4D_OBJECT_H
