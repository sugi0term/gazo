#include <stdio.h>
#include "iip.h"

void
divNxNImg(void);

int
main(int argc, char **argv)
{
	getData();
	rgbToYbr();
	divNxNImg();
	ybrToRgb();
	putData();

	return 0;
}

void
divNxNImg(void)
{
	int i, j;
	int vsp, hsp, div, x, y;

	printf("division: ");
	scanf("%d", &div);
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
