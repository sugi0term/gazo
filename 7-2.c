#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "iip.h"

void
normalizeFreq(void);

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s file [option ...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	getData(argv[1]);
	rgbToYbr();
	normalizeFreq();

	return 0;
}

void
normalizeFreq(void)
{
	int i, j, idx;
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
	
	printf("Max frequency: %d\n", maxFreq);
	for (i = 0; i < 256; i++) {
		val = ((double)freq[i] / maxFreq) * 100;
		printf("%3d: %4d --> %3d\n", i, freq[i], (int)round(val));
	}

}
