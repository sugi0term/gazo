#include <stdio.h>
#include <stdlib.h>
#include "iip.h"

void
divNxNImg(int);

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s file [option ...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	getData(argv[1]);
	rgbToYbr();
	divNxNImg(atoi(argv[3]));
	ybrToRgb();
	putData(argv[2]);

	return 0;
}

void
divNxNImg(int div)
{
	int i, j;
	int vsp, hsp, x, y;

	hsp = ptr->biWidth / div;
	vsp = ptr->biHeight / div;

	x = y = 0;
	for (i = 0; i < ptr->biWidth; i++) {
		for (j = 0; j < ptr->biHeight; j++) {
			if ((y < vsp && x < hsp) || (vsp <= y && hsp <= x)) {
				imgout[0][i][j] = imgin[0][i][j];
				imgout[1][i][j] = imgin[1][i][j];
				imgout[2][i][j] = imgin[2][i][j];
			}
			else {
				imgout[0][i][j] = 0;
				imgout[1][i][j] = 128;
				imgout[2][i][j] = 128;
			}
			y++;
			if (y == vsp * 2) y = 0;
		}
		x++;
		if (x == hsp * 2) x = 0;
	}
}
