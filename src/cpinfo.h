#ifndef CPINFO_H
#define CPINFO_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "utils.h"

#define CONSTANT_UTF8 1
#define CONSTANT_INT 3
#define CONSTANT_FLOAT 4
#define CONSTANT_LONG 5
#define CONSTANT_DOUBLE 6
#define CONSTANT_CLASSREF 7
#define CONSTANT_STRINGREF 8
#define CONSTANT_FIELDREF 9
#define CONSTANT_METHODREF 10
#define CONSTANT_INTERFACEMETHODREF 11
#define CONSTANT_NAMEANDTYPE 12
#define CONSTANT_METHODHANDLE 15
#define CONSTANT_METHODTYPE 16
#define CONSTANT_DYNAMIC 17
#define CONSTANT_INVOKEDYNAMIC 18
#define CONSTANT_MODULE 19
#define CONSTANT_PACKAGE 20

typedef struct
{
    uint16_t length;
    uint8_t *bytes;
} UTF8Info;

typedef struct {
    uint32_t value;
} IntInfo;

typedef struct {
    float value;
} FloatInfo;

typedef struct {
    uint64_t value;
} LongInfo;

typedef struct 
{
    double value;
} DoubleInfo;

typedef struct
{
    uint16_t nameIndex;
} ClassRefInfo;

typedef struct {
    uint16_t index;
} StringRefInfo;

// Info and Constant Pool Info

typedef union
{
    UTF8Info utf8inf;
    ClassRefInfo classInf;
    IntInfo intInf;
    FloatInfo floatInf;
    LongInfo longInf;
    DoubleInfo doubleInf;
    StringRefInfo stringInf;
} Info;

typedef struct
{
    uint8_t tag;
    Info info;
} CPInfo;

CPInfo *GetConstantPool(FILE *fp, int count);

#endif