#ifndef ADDLINFO_H
#define ADDLINFO_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "utils.h"

typedef struct
{
    /* data */
    uint16_t nameIndex;
    uint32_t length;
    uint8_t *info;
} AttrInfo;

typedef struct
{
    /* data */
    uint16_t accessFlags;
    uint16_t nameIndex;
    uint16_t descriptorIndex;
    uint16_t attrCount;
    AttrInfo *attributes;
} FieldInfo;

typedef struct
{
    /* data */
    uint16_t accessFlags;
    uint16_t nameIndex;
    uint16_t descriptorIndex;
    uint16_t attrCount;
    AttrInfo *attributes;
} MethodInfo;

AttrInfo ReadAttr(FILE *fp);
FieldInfo ReadField(FILE *fp);
MethodInfo ReadMethod(FILE *fp);

#endif