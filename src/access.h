#ifndef ACCESS_H
#define ACCESS_H

#include <stdint.h>
#include <stdbool.h>

#define ACCESS_PUBLIC 0x0001
#define ACCESS_FINAL 0x0010
#define ACCESS_SUPER 0x0020
#define ACCESS_INTERFACE 0x0200
#define ACCESS_ABSTRACT 0x0400
#define ACCESS_SYNTHETIC 0x1000
#define ACCESS_ANNOTATION 0x2000
#define ACCESS_ENUM 0x4000
#define ACCESS_MODULE 0x8000

bool IsAccessPublic(uint16_t accessFlag)
{
    return ACCESS_PUBLIC & accessFlag;
}

bool IsAccessFinal(uint16_t accessFlag)
{
    return ACCESS_FINAL & accessFlag;
}

bool IsAccessSuper(uint16_t accessFlag)
{
    return ACCESS_SUPER & accessFlag;
}

#endif