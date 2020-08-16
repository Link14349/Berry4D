#include <GLFW/glfw3.h>
#include "../include/camera.h"
#include "../include/scene.h"

void Camera::render() {
    auto& objects = scene->objects;
    rotationMatrix(-rotation.x, -rotation.y, -rotation.z, -rotation.w, A);
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
        float c = 0.01;
        for (auto body : bodys) {
            glBegin(GL_TRIANGLES);

            // 绘制三角形
            glColor3f(c, c, c);
            for (int i = 0; i < 2; i++) {
                for (int j = i + 1; j < 3; j++) {
                    for (int k = j + 1; k < 4; k++) {
                        glVertex3fv((GLfloat*)(TPoints + body->points[i]));
                        glVertex3fv((GLfloat*)(TPoints + body->points[j]));
                        glVertex3fv((GLfloat*)(TPoints + body->points[k]));
                    }
                }
            }
            c += 0.01;

            glEnd();

            // 绘制顶点连线
//            glBegin(GL_LINES);
//
//            glColor3f(1, 1, 1);
//            for (int i = 0; i < 3; i++)
//            {
//                for (int j = i + 1; j < 4; j++) {
//                    glVertex3fv((GLfloat*)(TPoints + body->points[i]));
//                    glVertex3fv((GLfloat*)(TPoints + body->points[j]));
//                }
//            }
//
//            glEnd();
        }
    }
}
