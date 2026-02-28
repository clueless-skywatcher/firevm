#ifndef UTILS_H
#define UTILS_H

#define BOOL(x) x > 0 ? "true" : "false"
#define RECAST(x, t) (*(t *) &x)

#include <stdio.h>
#include <stdint.h>

uint32_t ReadU4(FILE *fp);
uint16_t ReadU2(FILE *fp);
uint8_t ReadU1(FILE *fp);

#endif