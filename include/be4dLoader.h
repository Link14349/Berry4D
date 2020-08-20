#ifndef BERRY4D_BE4DLOADER_H
#define BERRY4D_BE4DLOADER_H

#include <string>
#include <fstream>
#include "object.h"

char* readFileCPTR(const std::string& filename, uint32_t& length);

class be4dLoader {
public:
    be4dLoader(const unsigned char* const c, uint32_t l) : content(c), len(l) { }
    Object* load();
private:
    static uint32_t parseUint32(const unsigned char*& c) {
        uint32_t s = 0;
        s |= ((*(c++)));
        s |= ((*(c++)) << 8);
        s |= ((*(c++)) << 16);
        s |= ((*(c++)) << 24);
        return s;
    }
    static float parseFloat(const unsigned char*& c) {
        uint32_t f = parseUint32(c);
        return *((float*)(&f));
    }
    const unsigned char* content;
    uint32_t len;
};


#endif //BERRY4D_BE4DLOADER_H
