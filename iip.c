#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "bmp.h"
#include "xfunc.h"
#include "iip.h"

uint8_t header[HEADER_LENGTH];
uint8_t imgin[3][2000][2000];
uint8_t imgout[3][2000][2000];
int alignment;
bmp_t *ptr;

void
getData(char *fn)
{
	FILE *fp;
	int i, j, k;

	fp = xfopen(fn, "r");

	fread(header, HEADER_LENGTH, 1, fp);
	ptr = (bmp_t *)header;
	alignment = ptr->bfSize - ptr->bfOffBits - ptr->biWidth * ptr->biHeight * (ptr->biBitCount / 8);

	for (i = ptr->biHeight - 1; 0 <= i; i--) {
		for (j = 0; j < ptr->biWidth; j++) {
			for (k = 2; 0 <= k; k--) {
				imgin[k][j][i] = fgetc(fp);
			}
		}
	}
}

void
putData(char *fn)
{
	int i, j, k;
	FILE *fp;

	fp = xfopen(fn, "w");

	fwrite(header, HEADER_LENGTH, 1, fp);

	for (i = ptr->biHeight - 1; 0 <= i; i--) {
		for (j = 0; j < ptr->biWidth; j++) {
			for (k = 2; 0 <= k; k--) {
				fputc(imgout[k][j][i], fp);
			}
		}
	}
	for (i = 0; i < alignment; i++) {
		fputc(0x00, fp);
	}
}

void processing()
{
	int i, j, k;

	for (k = 0; k < 3; k++) {
		for (i = 0; i < ptr->biWidth; i++) {
			for (j = 0; j < ptr->biHeight; j++) {
				imgout[k][i][j] = imgin[k][i][j];
			}
		}
	}
}

void
rgbToYbr(void)
{
	int i, j, k, m, n;
	double rgb[3] = {};
	double ycbcr[3] = {};
	double toYcbcr[][3] = {
		{0.2990, 0.5870, 0.1140},
		{-0.1687, -0.3313, 0.5000},
		{0.5000, -0.4187, -0.0813}
	};

	for (m = 0; m < ptr->biWidth; m++) {
		for (n = 0; n < ptr->biHeight; n++) {
			for (k = 0; k < 3; k++) {
				rgb[k] = imgin[k][m][n];
				ycbcr[k] = 0;
			}
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
					ycbcr[i] += toYcbcr[i][j] * rgb[j];
				}
			}

			for (i = 0; i < 3; i++) {
				ycbcr[i] = round(ycbcr[i]);
			}
			for (i = 1; i < 3; i++) {
				ycbcr[i] += 128;
			}
			for (i = 0; i < 3; i++) {
				if (255 < ycbcr[i]) ycbcr[i] = 255;
				if (ycbcr[i] < 0) ycbcr[i] = 0;
			}
			for (k = 0; k < 3; k++) {
				imgin[k][m][n] = ycbcr[k];
			}
		}
	}
}

void
ybrToRgb(void)
{
	int i, j, k, m, n;
	double rgb[3] = {};
	double ycbcr[3] = {};
	double toRgb[][3] = {
		{1.0000, 0.0000, 1.4020},
		{1.0000, -0.3441, -0.7141},
		{1.0000, 1.7720, 0.0000}
	};

	for (m = 0; m < ptr->biWidth; m++) {
		for (n = 0; n < ptr->biHeight; n++) {
			for (k = 0; k < 3; k++) {
				ycbcr[k] = imgout[k][m][n];
				rgb[k] = 0;
			}

			for (i = 1; i < 3; i++) {
				ycbcr[i] -= 128;
			}

			for (i = 0; i < 3; i++) {
				rgb[i] = 0;
				for (j = 0; j < 3; j++) {
					rgb[i] += toRgb[i][j] * ycbcr[j];
				}
			}

			for (i = 0; i < 3; i++) {
				rgb[i] = round(rgb[i]);
			}
			for (i = 0; i < 3; i++) {
				if (255 < rgb[i]) rgb[i] = 255;
				if (rgb[i] < 0) rgb[i] = 0;
			}
			for (k = 0; k < 3; k++) {
				imgout[k][m][n] = rgb[k];
			}
		}
	}
}
