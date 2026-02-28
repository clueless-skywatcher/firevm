#include "vm.h"
#include "access.h"

ClassStructure GetClassStructure(FILE *fp) {
    ClassStructure classStruct = {};
    classStruct.accessFlags = ReadU2(fp);
    classStruct.thisClass = ReadU2(fp);
    classStruct.superClass = ReadU2(fp);

    return classStruct;
}

ClassFile *ReadClassFile(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Failed to open file");
        return NULL;
    }
    fseek(fp, 0, 0);

    ClassFile *classFile = (ClassFile *) malloc(sizeof(ClassFile));

    uint32_t magic = ReadU4(fp);

    if (magic != CLASS_MAGIC) {
        perror("Invalid class file");
        return NULL;
    }

    classFile->magicNumber = magic;

    uint16_t minorVersion = ReadU2(fp);
    classFile->minorVersion = minorVersion;
    uint16_t majorVersion = ReadU2(fp);
    classFile->majorVersion = majorVersion;
    uint16_t cpCount = ReadU2(fp);
    classFile->constantPoolCount = cpCount;

    
    CPInfo *cpInfo = GetConstantPool(fp, cpCount);
    classFile->constantPool = cpInfo;

    ClassStructure classStruct = GetClassStructure(fp);
    classFile->classStructure = classStruct;

    uint16_t interfaceCount = ReadU2(fp);
    classFile->interfaceCount = interfaceCount;
    uint16_t *interfaces = (uint16_t *) malloc(interfaceCount);

    fclose(fp);
    return classFile;
}

void ShowClassFile(ClassFile *classFile) {
    printf("%u.%u %u\n", classFile->majorVersion, classFile->minorVersion, classFile->constantPoolCount);

    for (int i = 1; i <= classFile->constantPoolCount; i++) {
        if (classFile->constantPool[i].tag == CONSTANT_UTF8) {
            printf("#%d: UTF8 %s\n", i, classFile->constantPool[i].info.utf8inf.bytes);
        } else if (classFile->constantPool[i].tag == CONSTANT_CLASSREF) {
            uint16_t nameIndex = classFile->constantPool[i].info.classInf.nameIndex;
            printf("#%d: Class #%d // %s\n", i, nameIndex, classFile->constantPool[nameIndex].info.utf8inf.bytes);
        } else if (classFile->constantPool[i].tag == CONSTANT_STRINGREF) {
            uint16_t index = classFile->constantPool[i].info.stringInf.index;
            printf("#%d: String #%d // %s\n", i, index, classFile->constantPool[index].info.utf8inf.bytes);
        } else if (classFile->constantPool[i].tag == CONSTANT_INT) {
            printf("#%d: Integer %u\n", i, classFile->constantPool[i].info.intInf.value);
        } else if (classFile->constantPool[i].tag == CONSTANT_FLOAT) {
            printf("#%d: Float %f\n", i, classFile->constantPool[i].info.floatInf.value);
        } else if (classFile->constantPool[i].tag == CONSTANT_LONG) {
            printf("#%d: Long %lu\n", i, classFile->constantPool[i].info.longInf.value);
        } else if (classFile->constantPool[i].tag == CONSTANT_DOUBLE) {
            printf("#%d: Double %f\n", i, classFile->constantPool[i].info.doubleInf.value);
        }
    }

    ClassStructure classStruct = classFile->classStructure;

    printf("Public? = %s\n", BOOL(IsAccessPublic(classStruct.accessFlags)));
    printf("Final? = %s\n", BOOL(IsAccessFinal(classStruct.accessFlags)));
    printf("Super? = %s\n", BOOL(IsAccessSuper(classStruct.accessFlags)));

    printf("This class: #%d // %s\n", classStruct.thisClass, classFile->constantPool[classFile->constantPool[classStruct.thisClass].info.classInf.nameIndex].info.utf8inf.bytes);
    printf("Super class: #%d // %s\n", classStruct.superClass, classFile->constantPool[classFile->constantPool[classStruct.superClass].info.classInf.nameIndex].info.utf8inf.bytes);
}