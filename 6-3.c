#include <stdio.h>
#include <stdlib.h>
#include "iip.h"

void
quantizeImg(int);

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s src dest [option ...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	getData(argv[1]);
	rgbToYbr();
	quantizeImg(2);
	ybrToRgb();
	putData(argv[2]);

	return 0;
}

void
quantizeImg(int level)
{
	int i, j, k;
	int lowerLimit, upperLimit;
	int increment;

	increment = 256 / level;
	lowerLimit = 0;
	upperLimit = increment;
	for (k = 1; k <= level; k++) {
		for (i = 0; i < ptr->biWidth; i++) {
			for (j = 0; j < ptr->biHeight; j++) {
				if (lowerLimit <= imgin[0][i][j] && imgin[0][i][j] < upperLimit) {
					imgout[0][i][j] = upperLimit - (increment / 2);
					imgout[1][i][j] = 128;
					imgout[2][i][j] = 128;
				}
			}
		}
		lowerLimit += increment;
		upperLimit += increment;
	}
}
