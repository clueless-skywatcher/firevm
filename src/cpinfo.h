#ifndef CPINFO_H
#define CPINFO_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "utils.h"

#define CONSTANT_UTF8       1
#define CONSTANT_INT        3
#define CONSTANT_FLOAT      4
#define CONSTANT_LONG       5
#define CONSTANT_DOUBLE     6
#define CONSTANT_CLASSREF   7
#define CONSTANT_STRINGREF  8

typedef struct {
    uint16_t length;
    uint8_t *bytes;
} UTF8Info;

typedef struct {
    uint16_t nameIndex;
} ClassInfo;

typedef union {
    UTF8Info utf8inf;
    ClassInfo classInf;
} Info;

typedef struct {
    uint8_t tag;
    Info info;
} CPInfo;

CPInfo *GetConstantPool(FILE *fp, int count);

#endif