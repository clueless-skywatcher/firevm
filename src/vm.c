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
    for (int i = 0; i < interfaceCount; i++) {
        interfaces[i] = ReadU2(fp);
    }
    classFile->interfaces = interfaces;

    uint16_t fieldCount = ReadU2(fp);
    classFile->fieldCount = fieldCount;
    FieldInfo *fields = (FieldInfo *) malloc(fieldCount * sizeof(FieldInfo));
    for (int i = 0; i < fieldCount; i++) {
        fields[i] = ReadField(fp);
    }
    classFile->fields = fields;

    uint16_t methodCount = ReadU2(fp);
    classFile->methodCount = methodCount;
    MethodInfo *methods = (MethodInfo *) malloc(methodCount * sizeof(MethodInfo));
    for (int i = 0; i < methodCount; i++) {
        methods[i] = ReadMethod(fp);
    }
    classFile->methods = methods;
    
    fclose(fp);
    return classFile;
}

void ShowClassFile(ClassFile *classFile) {
    ClassStructure classStruct = classFile->classStructure;

    printf("Version: %u.%u\n", classFile->majorVersion, classFile->minorVersion);
    printf("Constant Pool Count: %u\n", classFile->constantPoolCount);
    printf("Interfaces: %u, Fields: %u, Methods: %u\n", classFile->interfaceCount, classFile->fieldCount, classFile->methodCount);
    printf("This class: #%d // %s\n", classStruct.thisClass, classFile->constantPool[classFile->constantPool[classStruct.thisClass].info.classInf.nameIndex].info.utf8inf.bytes);
    printf("Super class: #%d // %s\n", classStruct.superClass, classFile->constantPool[classFile->constantPool[classStruct.superClass].info.classInf.nameIndex].info.utf8inf.bytes);
    printf("Access Flags: 0x%04x\n", classStruct.accessFlags);
    printf("\tPublic? = %s\n", BOOL(IsAccessPublic(classStruct.accessFlags)));
    printf("\tFinal? = %s\n", BOOL(IsAccessFinal(classStruct.accessFlags)));
    printf("\tSuper? = %s\n", BOOL(IsAccessSuper(classStruct.accessFlags)));;
    
    printf("Constant Pool: \n");

    for (int i = 1; i <= classFile->constantPoolCount; i++) {
        if (classFile->constantPool[i].tag == CONSTANT_UTF8) {
            printf("\t#%d: UTF8 %s\n", i, classFile->constantPool[i].info.utf8inf.bytes);
        } else if (classFile->constantPool[i].tag == CONSTANT_CLASSREF) {
            uint16_t nameIndex = classFile->constantPool[i].info.classInf.nameIndex;
            printf("\t#%d: Class #%d // %s\n", i, nameIndex, classFile->constantPool[nameIndex].info.utf8inf.bytes);
        } else if (classFile->constantPool[i].tag == CONSTANT_STRINGREF) {
            uint16_t index = classFile->constantPool[i].info.stringInf.index;
            printf("\t#%d: String #%d // %s\n", i, index, classFile->constantPool[index].info.utf8inf.bytes);
        } else if (classFile->constantPool[i].tag == CONSTANT_INT) {
            printf("\t#%d: Integer %u\n", i, classFile->constantPool[i].info.intInf.value);
        } else if (classFile->constantPool[i].tag == CONSTANT_FLOAT) {
            printf("\t#%d: Float %f\n", i, classFile->constantPool[i].info.floatInf.value);
        } else if (classFile->constantPool[i].tag == CONSTANT_LONG) {
            printf("\t#%d: Long %lu\n", i, classFile->constantPool[i].info.longInf.value);
        } else if (classFile->constantPool[i].tag == CONSTANT_DOUBLE) {
            printf("\t#%d: Double %f\n", i, classFile->constantPool[i].info.doubleInf.value);
        }
    } 

    for (int i = 0; i < classFile->fieldCount; i++) {
        FieldInfo field = classFile->fields[i];
        printf("Field #%d: #%d AccessFlags=0x%04x // %s\n", i, field.nameIndex, field.accessFlags, classFile->constantPool[field.nameIndex].info.utf8inf.bytes);
    }

    for (int i = 0; i < classFile->methodCount; i++) {
        MethodInfo method = classFile->methods[i];
        printf("Method #%d: #%d AccessFlags=0x%04x // %s\n", i, method.nameIndex, method.accessFlags, classFile->constantPool[method.nameIndex].info.utf8inf.bytes);
    }
}