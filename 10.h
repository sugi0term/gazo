#ifndef _10_H_
#define _10_H_

#include "iip.h"

void
binarization(uint8_t [][SIZE][SIZE]);
void
contraction(uint8_t [][SIZE][SIZE]);
void
expansion(uint8_t [][SIZE][SIZE]);
int
exists(uint8_t [][SIZE][SIZE], int, int, int);
void
printImgInHex(uint8_t [][SIZE][SIZE]);
void
opening(uint8_t [][SIZE][SIZE], int);
void
closing(uint8_t [][SIZE][SIZE], int);

#define T 128
#define WHITE 255
#define BLACK 0

#endif
