#include "vm.h"
#include "access.h"

typedef struct {
    uint16_t accessFlags;
    uint16_t thisClass;
    uint16_t superClass;
} ClassStructure;

int ReadVM(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    fseek(fp, 0, 0);

    uint32_t magic = ReadU4(fp);

    if (magic != CLASS_MAGIC) {
        perror("Invalid class file");
        return EXIT_FAILURE;
    }

    uint16_t minorVersion = ReadU2(fp);
    uint16_t majorVersion = ReadU2(fp);
    uint16_t cpCount = ReadU2(fp);

    printf("%u.%u %u\n", majorVersion, minorVersion, cpCount);

    CPInfo *cpInfo = GetConstantPool(fp, cpCount);

    for (int i = 1; i <= cpCount; i++) {
        if (cpInfo[i].tag == CONSTANT_UTF8) {
            printf("#%d: UTF8 %s\n", i, cpInfo[i].info.utf8inf.bytes);
        } else if (cpInfo[i].tag == CONSTANT_CLASSREF) {
            uint16_t nameIndex = cpInfo[i].info.classInf.nameIndex;
            printf("#%d: Class #%d // %s\n", i, nameIndex, cpInfo[nameIndex].info.utf8inf.bytes);
        }
    }

    ClassStructure classStruct = {};
    classStruct.accessFlags = ReadU2(fp);
    classStruct.thisClass = ReadU2(fp);
    classStruct.superClass = ReadU2(fp);

    printf("Public? = %s\n", BOOL(IsAccessPublic(classStruct.accessFlags)));
    printf("Final? = %s\n", BOOL(IsAccessFinal(classStruct.accessFlags)));
    printf("Super? = %s\n", BOOL(IsAccessSuper(classStruct.accessFlags)));

    printf("This class: #%d // %s\n", classStruct.thisClass, cpInfo[classStruct.thisClass].info.utf8inf.bytes);
    printf("Super class: #%d // %s\n", classStruct.superClass, cpInfo[classStruct.superClass].info.utf8inf.bytes);

    fclose(fp);
    return EXIT_SUCCESS;
}