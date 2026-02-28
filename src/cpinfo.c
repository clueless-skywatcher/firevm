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
            break;
        }
        case CONSTANT_FLOAT:
        {
            uint32_t temp = ReadU4(fp);
            float floatConst = RECAST(temp, float);
            break;
        }
        case CONSTANT_LONG:
        {
            uint32_t longConst1 = ReadU4(fp);
            uint32_t longConst2 = ReadU4(fp);
            uint64_t longConst = (longConst1 << 32) | longConst2;
            break;
        }
        case CONSTANT_DOUBLE:
        {
            uint32_t longConst1 = ReadU4(fp);
            uint32_t longConst2 = ReadU4(fp);
            uint64_t temp = (longConst1 << 32) | longConst2;
            double doubleConst = RECAST(temp, double);
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
            ReadU2(fp);
            break;
        }
        default:
            ReadU4(fp);
            break;
        }
    }

    return constantPool;
}