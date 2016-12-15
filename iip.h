#ifndef _IIP_H_
#define _IIP_H_

#include "bmp.h"

#define HEADER_LENGTH 54
#define SIZE 512

void
getData(char *);
void
putData(char *);
void
rgbToYbr(uint8_t [][SIZE][SIZE]);
void
ybrToRgb(uint8_t [][SIZE][SIZE]);

enum RGB {
	R, G, B, nColors
};

enum YCbCr {
	Y, Cb, Cr
};

extern uint8_t header[HEADER_LENGTH];
extern uint8_t imgData[nColors][SIZE][SIZE];
extern int alignment;
extern bmp_t *imgHdr;

#endif
