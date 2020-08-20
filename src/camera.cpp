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
        float color = 0.1;
        const float step = .99 * .25 / bodys.size();
        for (auto body : bodys) {
//            if (objpos * *body->n > 0) continue;
//            if ((points[body->points[0]])->w < 0 || (points[body->points[1]])->w < 0 || (points[body->points[2]])->w < 0 || (points[body->points[3]])->w < 0) continue;
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < 2; i++) {
                for (int j = i + 1; j < 3; j++) {
                    for (int k = j + 1; k < 4; k++) {
                        auto p1 = TPoints + body->points[i], p2 = TPoints + body->points[j], p3 = TPoints + body->points[k];
//                        if ((points[body->points[i]])->w < 0 || (points[body->points[j]])->w < 0 || (points[body->points[k]])->w < 0) continue;
                        normal3D(norm3d, *p1, *p2, *p3);
                        norm3d *= 0.001f / norm3d.mod();
//                        // 光照计算
//                        auto material = body->material;
//                        // 环境光计算
//                        auto lightVal = scene->ambientLightColor % material->ra;
//                        // 漫反射光&镜面反射计算
//                        // 计算观察向量
//                        auto v = p1;
//                        v->inverse();// 这里改变了点的坐标，做完运算后还要改回来
//                        Color tmp1;
//                        Color tmp2;
//                        for (auto light : scene->lights) {
//                            auto l = (light->position - object->position).norm();
//                            if (isnan(l.x)) { l.x = l.y = l.z = l.w = 0; }
//                            if (body->n->operator*(l) < 0) continue;
//                            // 计算漫反射
//                            tmp1 += light->color * body->n->operator*(l);
//                            // 计算镜面反射
//                            l.x *= -1;
//                            l.z *= -1;
//                            auto r_v = v->operator*(l);
//                            if (r_v <= 0) continue;
//                            tmp2 += light->color * std::pow(r_v, material->power);
//                        }
//                        tmp1 %= material->rd;
//                        lightVal += tmp1;
//                        tmp2 %= material->rs;
//                        lightVal += tmp2;
//                        Color clr = lightVal % material->color + material->color * AMIBIENT;// 各种光照合成后的表面颜色
//                        // 完成计算
//                        v->inverse();// 将点的坐标恢复回去
//                        glColor3f(clr.r, clr.g, clr.b);
                        glColor3f(.1 + norm3d.y * 50, .7 + norm3d.y * 500, .5 + norm3d.y * 200);
//                        norm3d *= 0.001f;
                        (TPoints + body->points[i])->operator+=(norm3d);
                        (TPoints + body->points[j])->operator+=(norm3d);
                        (TPoints + body->points[k])->operator+=(norm3d);
                        glVertex3fv((GLfloat*)(TPoints + body->points[i]));
                        glVertex3fv((GLfloat*)(TPoints + body->points[j]));
                        glVertex3fv((GLfloat*)(TPoints + body->points[k]));
                        (TPoints + body->points[i])->operator-=(norm3d);
                        (TPoints + body->points[j])->operator-=(norm3d);
                        (TPoints + body->points[k])->operator-=(norm3d);
                        color += step;
                    }
                }
            }
//            c += 0.00000001f;
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
