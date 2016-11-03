#include <stdio.h>
#include <stdlib.h>
#include "iip.h"

void
mosaicImg(int);

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s src dest [option ...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	getData(argv[1]);
	rgbToYbr();
	mosaicImg(2);
	ybrToRgb();
	putData(argv[2]);

	return 0;
}

void
mosaicImg(int blockSize)
{
	int i, j, m, n;
	int sum, ave;

	for (i = 0; i < ptr->biWidth; i += blockSize) {
		for (j = 0; j < ptr->biHeight; j += blockSize) {
			sum = 0;
			for (m = i; m < i + blockSize; m++) {
				for (n = j; n < j + blockSize; n++) {
					sum += imgin[0][m][n];
				}
			}
			ave = sum / (blockSize * blockSize);
			for (m = i; m < i + blockSize; m++) {
				for (n = j; n < j + blockSize; n++) {
					imgout[0][m][n] = ave;
					imgout[1][m][n] = 128;
					imgout[2][m][n] = 128;
				}
			}
		}
	}
}
