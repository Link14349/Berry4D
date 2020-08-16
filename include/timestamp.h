#ifndef BERRY3D_TIMESTAMP_H
#define BERRY3D_TIMESTAMP_H

#include <cstdint>
#include <sys/time.h>
#include <cstdlib>

int64_t getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

#endif //BERRY3D_TIMESTAMP_H
