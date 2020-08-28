#include "../include/be4dLoader.h"
#include <cstring>

char* readFileCPTR(const std::string& filename, uint32_t& length) {
    std::ifstream t;
    char* buffer;
    t.open(filename, std::ios::in | std::ios::binary);
    if (!t.is_open() || !t) {
        t.close();
        length = 0;
        return nullptr;
    }
    t.seekg(0, std::ios::end);
    length = t.tellg();
    t.seekg(0, std::ios::beg);
    buffer = new char[length];
    t.read(buffer, length);
    t.close();
    return buffer;
}

Object *be4dLoader::load() {
    if (content[0] != 'b' || content[1] != 'e' || content[2] != '4' || content[3] != 'f') return nullptr;
    Object* object = new Object;
    auto adr = content + 5;
    switch (*adr) {
        case '\x03': {// 3d模型
            adr++;
            auto planeIdx = parseUint32(adr);
            adr += 8;// 跳过8bytes的备用区域
            auto planeAdr = content + planeIdx;
            while (adr < planeAdr) {
                float x = parseFloat(adr), y = parseFloat(adr), z = parseFloat(adr);
                object->points.push_back(new Vector4(x, y, z, 0));
                object->rawPoints.push_back(new Vector4(x, y, z, 0));
            }
            if (adr > planeAdr) {// 说明地址有误
                delete object;
                return nullptr;
            }
            while (adr < content + len) {
                uint32_t a = parseUint32(adr), b = parseUint32(adr), c = parseUint32(adr);
                auto t1 = new Vector4(*object->points[a]), t2 = new Vector4(*object->points[a]);
                t1->w = 0.001, t2->w = 0.001;
                object->points.push_back(t1);
                object->rawPoints.push_back(t2);
                object->bodys.push_back(new Object::Body(new Vector4, a, b, c, object->points.size() - 1));
                object->rawNormals.push_back(new Vector4);
            }
            object->normal();
            break;
        }
        case '\x04': {// 4d模型
            adr++;
            auto bodyIdx = parseUint32(adr);
            adr += 8;// 跳过8bytes的备用区域
            auto bodyAdr = content + bodyIdx;
            while (adr < bodyAdr) {
                float x = parseFloat(adr), y = parseFloat(adr), z = parseFloat(adr), w = parseFloat(adr);
                object->points.push_back(new Vector4(x, y, z, w));
                object->rawPoints.push_back(new Vector4(x, y, z, w));
            }
            if (adr > bodyAdr) {// 说明地址有误
                delete object;
                return nullptr;
            }
            while (adr < content + len) {
                uint32_t a = parseUint32(adr), b = parseUint32(adr), c = parseUint32(adr), d = parseUint32(adr);
                object->bodys.push_back(new Object::Body(new Vector4, a, b, c, d));
                object->rawNormals.push_back(new Vector4);
            }
            object->normal();
            break;
        }
    }
    object->getRadius();
//    object->rotate(Vector4(0.001, 0.001, 0.001, 0.001));
    return object;
}

void be4dLoader::write(FILE* file, Object* object) {
    auto c = new char[18 + 16 * object->points.size() + 16 * object->bodys.size()];
    uint32_t idx = 6;
    strcpy(c, "be4f\x01\x04");// 1版本号00; 1文件类型4d模型; 4占位符，存planes存储地址; 8备用空间，暂无用处
    u32Bin(18 + object->points.size() * 16, c, idx);
    idx = 18;
    auto& points = object->points;
    auto& bodies = object->bodys;
    for (auto point : points) {
        floatBin(point->x, c, idx);
        floatBin(point->y, c, idx);
        floatBin(point->z, c, idx);
        floatBin(point->w, c, idx);
    }
    for (auto body : bodies) {
        u32Bin(body->points[0], c, idx);
        u32Bin(body->points[1], c, idx);
        u32Bin(body->points[2], c, idx);
        u32Bin(body->points[3], c, idx);
    }
    fwrite(c, idx , 1, file);
    delete[] c;
}
