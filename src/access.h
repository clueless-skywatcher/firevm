#ifndef ACCESS_H
#define ACCESS_H

#include <stdint.h>

#define ACCESS_PUBLIC   0x0001
#define ACCESS_FINAL    0x0010
#define ACCESS_SUPER    0x0020

bool IsAccessPublic(uint16_t accessFlag) {
    return ACCESS_PUBLIC & accessFlag;
}

bool IsAccessFinal(uint16_t accessFlag) {
    return ACCESS_FINAL & accessFlag;
}

bool IsAccessSuper(uint16_t accessFlag) {
    return ACCESS_SUPER & accessFlag;
}

#endif