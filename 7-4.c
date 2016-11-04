#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "iip.h"

void
contrast(void);

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s src dest [option ...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	getData(argv[1]);
	rgbToYbr();
	contrast();
	ybrToRgb();
	putData(argv[2]);

	return 0;
}

void
contrast(void)
{
	int i, j, k;
	int max, min;
	double val;

	max = min = imgin[0][0][0];

	for (i = 0; i < ptr->biWidth; i++) {
		for (j = 0; j < ptr->biHeight; j++) {
			if (max < imgin[0][i][j]) {
				max = imgin[0][i][j];
			}
			if (imgin[0][i][j] < min) {
				min = imgin[0][i][j];
			}
		}
	}

	for (i = 0; i < ptr->biWidth; i++) {
		for (j = 0; j < ptr->biHeight; j++) {
			val = ((double)255 / (max - min));
			val *= (imgin[0][i][j] - min);
			imgout[0][i][j] = (int)round(val);
		}
	}

	for (i = 0; i < ptr->biWidth; i++) {
		for (j = 0; j < ptr->biHeight; j++) {
			for (k = 1; k < 3; k++) {
				imgout[k][i][j] = imgin[k][i][j];
			}
		}
	}
}
