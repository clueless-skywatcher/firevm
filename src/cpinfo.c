#include "cpinfo.h"

CPInfo *GetConstantPool(FILE *fp, int count)
{
    CPInfo *constantPool = (CPInfo *)malloc(sizeof(CPInfo) * count);

    for (int i = 1; i < count; i++)
    {
        uint8_t tag = ReadU1(fp);
        constantPool[i].tag = tag;

        switch (tag)
        {
        case CONSTANT_INT:
        {
            uint32_t intConst = ReadU4(fp);
            constantPool[i].info.intInf.value = intConst;
            break;
        }
        case CONSTANT_FLOAT:
        {
            uint32_t temp = ReadU4(fp);
            float floatConst = RECAST(temp, float);
            constantPool[i].info.floatInf.value = floatConst;
            break;
        }
        case CONSTANT_LONG:
        {
            uint32_t longConst1 = ReadU4(fp);
            uint32_t longConst2 = ReadU4(fp);
            constantPool[i].info.longInf.value = (longConst1 << 32) | longConst2;
            break;
        }
        case CONSTANT_DOUBLE:
        {
            uint32_t longConst1 = ReadU4(fp);
            uint32_t longConst2 = ReadU4(fp);
            uint64_t temp = (longConst1 << 32) | longConst2;
            constantPool[i].info.doubleInf.value = RECAST(temp, double);
            break;
        }
        case CONSTANT_UTF8:
        {
            uint16_t len = ReadU2(fp);
            constantPool[i].info.utf8inf.length = len;
            constantPool[i].info.utf8inf.bytes = (uint8_t *)malloc(len + 1);
            fread(constantPool[i].info.utf8inf.bytes, 1, len, fp);
            constantPool[i].info.utf8inf.bytes[len] = '\0';
            break;
        }
        case CONSTANT_CLASSREF:
        {
            constantPool[i].info.classInf.nameIndex = ReadU2(fp);
            break;
        }
        case CONSTANT_STRINGREF:
        {
            constantPool[i].info.stringInf.index = ReadU2(fp);
            break;
        }
        case CONSTANT_FIELDREF:
        case CONSTANT_METHODREF:
        case CONSTANT_INTERFACEMETHODREF:
        case CONSTANT_NAMEANDTYPE:
        case CONSTANT_METHODHANDLE:
        case CONSTANT_METHODTYPE:
        case CONSTANT_DYNAMIC:
        case CONSTANT_INVOKEDYNAMIC:
        case CONSTANT_MODULE:
        case CONSTANT_PACKAGE:
        default:
            ReadU4(fp);
            break;
        }
    }

    return constantPool;
}