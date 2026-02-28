#include "utils.h"

uint32_t ReadU4(FILE *fp)
{
    uint8_t b1 = ReadU1(fp);
    uint8_t b2 = ReadU1(fp);
    uint8_t b3 = ReadU1(fp);
    uint8_t b4 = ReadU1(fp);

    return (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
}

uint16_t ReadU2(FILE *fp)
{
    uint8_t b1 = ReadU1(fp);
    uint8_t b2 = ReadU1(fp);
    return (b1 << 8) | b2;
}

uint8_t ReadU1(FILE *fp)
{
    return fgetc(fp);
}
