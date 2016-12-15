#include <stdio.h>
#include <stdlib.h>
#include "iip.h"
#include "10.h"

int
main(int argc, char **argv)
{
	if (argc < 3) {
		fprintf(stderr, "usage: %s infile outfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	getData(argv[1]);
	rgbToYbr(imgData);
	binarization(imgData);
	ybrToRgb(imgData);
	putData(argv[2]);

	return 0;
}

