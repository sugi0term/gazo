#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "iip.h"

void
drawHistogram(void);

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s src dest [option ...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	getData(argv[1]);
	rgbToYbr();
	drawHistogram();
	ybrToRgb();
	putData(argv[2]);

	return 0;
}

void
drawHistogram(void)
{
	int i, j, k, idx;
	int freq[256] = {};
	int maxFreq;
	double val;

	maxFreq = 0;
	for (i = 0; i < ptr->biWidth; i++) {
		for (j = 0; j < ptr->biHeight; j++) {
			idx = imgin[0][i][j];
			freq[idx]++;
			if (maxFreq < freq[idx]) {
				maxFreq = freq[idx];
			}
		}
	}
	
	for (i = 0; i < 256; i++) {
		val = ((double)freq[i] / maxFreq) * 100;
		freq[i] = (int)round(val);
	}

	for (i = 0; i < ptr->biWidth; i++) {
		for (j = 0; j < ptr->biHeight; j++) {
			for (k = 0; k < 3; k++) {
				imgout[k][i][j] = imgin[k][i][j];
			}
		}
	}

	for (i = 0; i < 256; i++) {
		for (j = 1; j <= 100; j++) {
			imgout[0][i][ptr->biHeight - j] = 0x00;
			imgout[1][i][ptr->biHeight - j] = 0x80;
			imgout[2][i][ptr->biHeight - j] = 0x80;
		}
	}
			
	for (i = 0; i < 256; i++) {
		for (j = 1; j <= freq[i]; j++) {
			imgout[0][i][ptr->biHeight - j] = 0x00;
			imgout[1][i][ptr->biHeight - j] = 0x80;
			imgout[2][i][ptr->biHeight - j] = 0xff;
		}
	}
}
