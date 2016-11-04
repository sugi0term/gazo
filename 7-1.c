#include <stdio.h>
#include <stdlib.h>
#include "iip.h"

void
printFreq(void);

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s file [option ...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	getData(argv[1]);
	rgbToYbr();
	printFreq();

	return 0;
}

void
printFreq(void)
{
	int i, j;
	int freq[256] = {};

	for (i = 0; i < ptr->biWidth; i++) {
		for (j = 0; j < ptr->biHeight; j++) {
			freq[imgin[0][i][j]]++;
		}
	}

	for (i = 0; i < 256; i++) {
		printf("%3d: %4d\n", i, freq[i]);
	}

}
