#ifndef VM_H
#define VM_H

#define CLASS_MAGIC 0xCAFEBABE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils.h"
#include "cpinfo.h"

int ReadVM(char *filename);

#endif