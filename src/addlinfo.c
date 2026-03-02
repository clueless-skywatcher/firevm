#include "addlinfo.h"

FieldInfo ReadField(FILE *fp, CPInfo *cp)
{
    FieldInfo field = {};

    field.accessFlags = ReadU2(fp);
    field.nameIndex = ReadU2(fp);
    field.descriptorIndex = ReadU2(fp);
    field.attrCount = ReadU2(fp);

    AttrInfo *attrs = (AttrInfo *) malloc(sizeof(AttrInfo) * field.attrCount);

    for (int i = 0; i < field.attrCount; i++) {
        attrs[i] = ReadAttr(fp, cp);
    }

    field.attributes = attrs;
    return field;
}

void ShowField(FieldInfo fieldInfo)
{
    printf("\tAccess Flags: %u\n", fieldInfo.accessFlags);
    printf("\tName Index: %u\n", fieldInfo.nameIndex);
    printf("\tDescriptor Index: %u\n", fieldInfo.descriptorIndex);
    printf("\tAttribute Count: %u\n", fieldInfo.attrCount);
    for (int i = 0; i < fieldInfo.attrCount; i++) {
        printf("\t\tAttribute: %s\n", fieldInfo.attributes[i].name);
    }
}

MethodInfo ReadMethod(FILE *fp, CPInfo *cp)
{
    MethodInfo method = {};

    method.accessFlags = ReadU2(fp);
    method.nameIndex = ReadU2(fp);
    method.descriptorIndex = ReadU2(fp);
    method.attrCount = ReadU2(fp);

    AttrInfo *attrs = (AttrInfo *) malloc(sizeof(AttrInfo) * method.attrCount);

    for (int i = 0; i < method.attrCount; i++) {
        attrs[i] = ReadAttr(fp, cp);
    }

    method.attributes = attrs;

    return method;
}

void ShowMethod(MethodInfo methodInfo)
{
    printf("\tAccess Flags: %u\n", methodInfo.accessFlags);
    printf("\tName Index: %u\n", methodInfo.nameIndex);
    printf("\tDescriptor Index: %u\n", methodInfo.descriptorIndex);
    printf("\tAttribute Count: %u\n", methodInfo.attrCount);
    for (int i = 0; i < methodInfo.attrCount; i++) {
        printf("\t\tAttribute: %s\n", methodInfo.attributes[i].name);
    }
}

AttrInfo ReadAttr(FILE *fp, CPInfo *cp) {
    AttrInfo attrInfo = {};
    attrInfo.nameIndex = ReadU2(fp);
    attrInfo.name = (char *) cp[attrInfo.nameIndex].info.utf8inf.bytes;
    attrInfo.length = ReadU4(fp);

    uint8_t *attrs = (uint8_t *) malloc(attrInfo.length * sizeof(uint8_t));

    for (int i = 0; i < attrInfo.length; i++) {
        attrs[i] = ReadU1(fp);
    }

    attrInfo.info = attrs;

    return attrInfo;
}

void ShowAttr(AttrInfo attrInfo)
{
    printf("\tName Index: %u\n", attrInfo.nameIndex);
    printf("\tLength: %u\n", attrInfo.length);
}
