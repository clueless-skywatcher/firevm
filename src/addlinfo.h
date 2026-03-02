#ifndef ADDLINFO_H
#define ADDLINFO_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "cpinfo.h"
#include "utils.h"

typedef struct
{
    /* data */
    uint16_t nameIndex;
    char *name;
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

AttrInfo ReadAttr(FILE *fp, CPInfo *cp);
void ShowAttr(AttrInfo attrInfo);

FieldInfo ReadField(FILE *fp, CPInfo *cp);
void ShowField(FieldInfo fieldInfo);

MethodInfo ReadMethod(FILE *fp, CPInfo *cp);
void ShowMethod(MethodInfo methodInfo);

#endif