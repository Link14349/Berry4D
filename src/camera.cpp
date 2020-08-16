#include <GLFW/glfw3.h>
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
        float c = -1;
        const float step = .5f / bodys.size();
        struct Plane {
            Plane(float a, float b, float c, float d) : x(a), y(b), z(c), r(d) { }
            float x, y, z, r;
        };
        std::map<uint64_t, Plane*> planes;
        for (auto body : bodys) {
            if (body->n->operator*(position) > 0) continue;
//            glEnable(GL_POLYGON_OFFSET_FILL);
            glBegin(GL_TRIANGLES);
            for (int i = 0; i < 2; i++) {
                for (int j = i + 1; j < 3; j++) {
                    for (int k = j + 1; k < 4; k++) {
                        // 计算颜色&根据法线编码出map的id
                        constexpr char l = 7;
                        constexpr float BL = 1 << l;
                        auto p1 = TPoints + body->points[i], p2 = TPoints + body->points[j], p3 = TPoints + body->points[k];
                        normal3D(norm3d, *p1, *p2, *p3);
                        uint64_t t = 0;
                        norm3d.x < 0 ? t |= 1 : 0, t <<= 1;
                        norm3d.y < 0 ? t |= 1 : 0, t <<= 1;
                        norm3d.z < 0 ? t |= 1 : 0, t <<= l;
                        norm3d.x = abs(norm3d.x);
                        norm3d.y = abs(norm3d.y);
                        norm3d.z = abs(norm3d.z);
                        (t |= (uint32_t)(norm3d.x * (BL))) <<= l;
                        (t |= (uint32_t)(norm3d.y * (BL))) <<= l;
                        t |= (uint32_t)(norm3d.z * (BL));
                        float x, y, z, r1, r2, r3;
                        x = (p1->x + p2->x) * .5;
                        y = (p1->y + p2->y) * .5;
                        z = (p1->z + p2->z) * .5;
                        r1 = (x - p1->x) * (x - p1->x) + (y - p1->y) * (y - p1->y) + (z - p1->z) * (z - p1->z);
                        r2 = (x - p2->x) * (x - p2->x) + (y - p2->y) * (y - p2->y) + (z - p2->z) * (z - p2->z);
                        r3 = (x - p3->x) * (x - p3->x) + (y - p3->y) * (y - p3->y) + (z - p3->z) * (z - p3->z);
                        if (r1 < r2) r1 = r2;
                        if (r1 < r3) r1 = r3;
                        decltype(planes.find(t)) it;
                        if ((it = planes.find(t)) != planes.end()) {
                            auto plane = it->second;
                            if ((plane->x - x) * (plane->x - x) + (plane->y - y) * (plane->y - y) + (plane->z - z) * (plane->z - z) <= r1 + plane->r) {
                                continue;
                            }
                        }
                        planes[t] = new Plane(x, y, z, r1);
                        if (norm3d.mod() != 0) norm3d *= 1 / norm3d.mod();
                        else norm3d.x = norm3d.y = norm3d.z = .5;

                        // 绘制
                        glPolygonOffset(1, c);
                        glColor3f(norm3d.x, norm3d.y, norm3d.z);
//                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        glVertex3fv((GLfloat*)p1);
                        glVertex3fv((GLfloat*)p2);
                        glVertex3fv((GLfloat*)p3);
                        c += step;
                    }
                }
            }
            glEnd();
//            glDisable(GL_POLYGON_OFFSET_FILL);

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
        for (auto plane : planes) delete plane.second;
    }
}
