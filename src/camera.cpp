#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
#include <map>
#include "../include/camera.h"
#include "../include/scene.h"

void Camera::render() {
    auto& objects = scene->objects;
    rotationMatrix(-rotation.x, -rotation.y, -rotation.z, -rotation.w, A);
    Vector4 norm3d;// 用于存储投影体的某个面3d法线
    for (auto object : objects) {
        Vector4 TPoints[object->points.size()];
        auto& objpos = object->position;
        auto& points = object->points;
        auto& bodys = object->bodys;
        Vector4* tpoint = TPoints;
        for (auto point : points) {
            tpoint->operator=(*point);
            tpoint->operator+=(objpos);
            tpoint->operator-=(position);
            tpoint->rotate(A);
            tpoint->x /= tpoint->w * TAN_hfov_x;
            tpoint->y /= tpoint->w * TAN_hfov_y;
            tpoint->z /= tpoint->w * TAN_hfov_z;
            tpoint++;
        }
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        float c = 0;
        for (auto body : bodys) {
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < 2; i++) {
                for (int j = i + 1; j < 3; j++) {
                    for (int k = j + 1; k < 4; k++) {
                        auto p1 = TPoints + body->points[i], p2 = TPoints + body->points[j], p3 = TPoints + body->points[k];
                        normal3D(norm3d, *p1, *p2, *p3);
                        norm3d *= 1 / norm3d.mod();
                        norm3d *= .5;
                        if (norm3d.z < 0) norm3d *= -1;
                        norm3d += .5;
                        glColor3f(norm3d.x, norm3d.y, norm3d.z);
                        norm3d *= c;
                        (TPoints + body->points[i])->operator+=(norm3d);
                        (TPoints + body->points[j])->operator+=(norm3d);
                        (TPoints + body->points[k])->operator+=(norm3d);
                        glVertex3fv((GLfloat*)(TPoints + body->points[i]));
                        glVertex3fv((GLfloat*)(TPoints + body->points[j]));
                        glVertex3fv((GLfloat*)(TPoints + body->points[k]));
                        (TPoints + body->points[i])->operator-=(norm3d);
                        (TPoints + body->points[j])->operator-=(norm3d);
                        (TPoints + body->points[k])->operator-=(norm3d);
                    }
                }
            }
            c += 0.00001f;
            glEnd();

//            glBegin(GL_LINES);
//            glColor3f(1, 1, 1);
//            for (int i = 0; i < 3; i++) {
//                for (int j = i + 1; j < 4; j++) {
//                    glVertex3fv((GLfloat*)(TPoints + body->points[i]));
//                    glVertex3fv((GLfloat*)(TPoints + body->points[j]));
//                }
//            }
//            glEnd();
        }
    }
}
