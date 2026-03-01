#include "addlinfo.h"

FieldInfo ReadField(FILE *fp)
{
    FieldInfo field = {};

    field.accessFlags = ReadU2(fp);
    field.nameIndex = ReadU2(fp);
    field.descriptorIndex = ReadU2(fp);
    field.attrCount = ReadU2(fp);

    AttrInfo *attrs = (AttrInfo *) malloc(sizeof(AttrInfo) * field.attrCount);

    for (int i = 0; i < field.attrCount; i++) {
        attrs[i] = ReadAttr(fp);
    }

    field.attributes = attrs;

    return field;
}

MethodInfo ReadMethod(FILE *fp)
{
    MethodInfo method = {};

    method.accessFlags = ReadU2(fp);
    method.nameIndex = ReadU2(fp);
    method.descriptorIndex = ReadU2(fp);
    method.attrCount = ReadU2(fp);

    AttrInfo *attrs = (AttrInfo *) malloc(sizeof(AttrInfo) * method.attrCount);

    for (int i = 0; i < method.attrCount; i++) {
        attrs[i] = ReadAttr(fp);
    }

    method.attributes = attrs;

    return method;
}

AttrInfo ReadAttr(FILE *fp)
{
    AttrInfo attrInfo = {};
    attrInfo.nameIndex = ReadU2(fp);
    attrInfo.length = ReadU4(fp);

    uint8_t *attrs = (uint8_t *) malloc(attrInfo.length * sizeof(uint8_t));

    for (int i = 0; i < attrInfo.length; i++) {
        attrs[i] = ReadU1(fp);
    }

    attrInfo.info = attrs;

    return attrInfo;
}
