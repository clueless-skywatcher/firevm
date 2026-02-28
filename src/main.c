#include "vm.h"

int main(int argc, char **argv) {
    ClassFile *file = ReadClassFile(argv[1]);
    ShowClassFile(file);
}