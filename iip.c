#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "bmp.h"
#include "xfunc.h"
#include "iip.h"

uint8_t header[HEADER_LENGTH];
uint8_t imgData[nColors][SIZE][SIZE];
int alignment;
bmp_t *imgHdr;

void
getData(char *fn)
{
	FILE *fp;
	int i, j, k;

	fp = xfopen(fn, "r");

	fread(header, sizeof(header), 1, fp);
	imgHdr = (bmp_t *)header;
	alignment = imgHdr->bfSize - imgHdr->bfOffBits - imgHdr->biWidth * imgHdr->biHeight * (imgHdr->biBitCount / 8);

	for (i = imgHdr->biHeight - 1; 0 <= i; i--) {
		for (j = 0; j < imgHdr->biWidth; j++) {
			for (k = nColors - 1; 0 <= k; k--) {
				imgData[k][j][i] = fgetc(fp);
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

	fwrite(header, sizeof(header), 1, fp);

	for (i = imgHdr->biHeight - 1; 0 <= i; i--) {
		for (j = 0; j < imgHdr->biWidth; j++) {
			for (k = nColors - 1; 0 <= k; k--) {
				fputc(imgData[k][j][i], fp);
			}
		}
	}
	for (i = 0; i < alignment; i++) {
		fputc(0, fp);
	}
}

void
rgbToYbr(uint8_t imgData[][SIZE][SIZE])
{
	int i, j, k, m, n;
	double rgb[nColors] = {};
	double ycbcr[nColors] = {};
	double toYcbcr[][nColors] = {
		{0.2990, 0.5870, 0.1140},
		{-0.1687, -0.3313, 0.5000},
		{0.5000, -0.4187, -0.0813}
	};

	for (m = 0; m < imgHdr->biWidth; m++) {
		for (n = 0; n < imgHdr->biHeight; n++) {
			for (k = 0; k < nColors; k++) {
				rgb[k] = imgData[k][m][n];
				ycbcr[k] = 0;
			}
			for (i = 0; i < nColors; i++) {
				for (j = 0; j < nColors; j++) {
					ycbcr[i] += toYcbcr[i][j] * rgb[j];
				}
			}

			for (i = 0; i < nColors; i++) {
				ycbcr[i] = round(ycbcr[i]);
			}
			for (i = 1; i < nColors; i++) {
				ycbcr[i] += 128;
			}
			for (i = 0; i < nColors; i++) {
				if (255 < ycbcr[i]) ycbcr[i] = 255;
				if (ycbcr[i] < 0) ycbcr[i] = 0;
			}
			for (k = 0; k < nColors; k++) {
				imgData[k][m][n] = ycbcr[k];
			}
		}
	}
}

void
ybrToRgb(uint8_t imgData[][SIZE][SIZE])
{
	int i, j, k, m, n;
	double rgb[nColors] = {};
	double ycbcr[nColors] = {};
	double toRgb[][nColors] = {
		{1.0000, 0.0000, 1.4020},
		{1.0000, -0.3441, -0.7141},
		{1.0000, 1.7720, 0.0000}
	};

	for (m = 0; m < imgHdr->biWidth; m++) {
		for (n = 0; n < imgHdr->biHeight; n++) {
			for (k = 0; k < nColors; k++) {
				ycbcr[k] = imgData[k][m][n];
				rgb[k] = 0;
			}

			for (i = 1; i < nColors; i++) {
				ycbcr[i] -= 128;
			}

			for (i = 0; i < nColors; i++) {
				rgb[i] = 0;
				for (j = 0; j < nColors; j++) {
					rgb[i] += toRgb[i][j] * ycbcr[j];
				}
			}

			for (i = 0; i < nColors; i++) {
				rgb[i] = round(rgb[i]);
			}
			for (i = 0; i < nColors; i++) {
				if (255 < rgb[i]) rgb[i] = 255;
				if (rgb[i] < 0) rgb[i] = 0;
			}
			for (k = 0; k < nColors; k++) {
				imgData[k][m][n] = rgb[k];
			}
		}
	}
}
