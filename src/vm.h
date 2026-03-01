#ifndef VM_H
#define VM_H

#define CLASS_MAGIC 0xCAFEBABE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils.h"
#include "cpinfo.h"
#include "addlinfo.h"

typedef struct {
    uint16_t accessFlags;
    uint16_t thisClass;
    uint16_t superClass;
} ClassStructure;

typedef struct {
    uint32_t magicNumber;
    uint16_t minorVersion;
    uint16_t majorVersion;
    uint16_t constantPoolCount;
    CPInfo *constantPool;
    ClassStructure classStructure;
    uint16_t interfaceCount;
    uint16_t *interfaces;
    uint16_t fieldCount;
    FieldInfo *fields;
    uint16_t methodCount;
    MethodInfo *methods;
    uint16_t attributeCount;
    AttrInfo *attributes;
} ClassFile;

ClassFile *ReadClassFile(char *filename);
void ShowClassFile(ClassFile *classFile);

ClassStructure GetClassStructure(FILE *fp);

#endif