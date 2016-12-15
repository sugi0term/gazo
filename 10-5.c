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
	puts("＜入力信号＞");
	printImgInHex(imgData);
	printf("\n");
	binarization(imgData);
	puts("＜２値化信号＞");
	printImgInHex(imgData);
	printf("\n");
	closing(imgData, 2);
	puts("＜クロージング後の２値化信号＞");
	printImgInHex(imgData);
	printf("\n");
	ybrToRgb(imgData);
	putData(argv[2]);

	return 0;
}

