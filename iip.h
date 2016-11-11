#ifndef _IIP_H_
#define _IIP_H_

#include "bmp.h"

#define HEADER_LENGTH 54

void
getData(char *);
void
putData(char *);
void
processing(void);
void
rgbToYbr(void);
void
ybrToRgb(void);

extern uint8_t header[HEADER_LENGTH];
extern uint8_t imgin[3][2000][2000];
extern uint8_t imgout[3][2000][2000];
extern int alignment;
extern bmp_t *ptr;

#endif
