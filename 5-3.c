#include "iip.h"

void
div2x2Img(void);

int
main(int argc, char **argv)
{
	getData();
	rgbToYbr();
	div2x2Img();
	ybrToRgb();
	putData();

	return 0;
}

void
div2x2Img(void)
{
	int i, j, k;
	int vsp, hsp;

	hsp = ptr->biWidth / 2;
	vsp = ptr->biHeight / 2;
	for (k = 0; k < 3; k++) {
		for (i = 0; i < ptr->biWidth; i++) {
			for (j = 0; j < ptr->biHeight; j++) {
				imgout[k][i][j] = imgin[k][i][j];
			}
		}
	}
	for (i = hsp; i < ptr->biWidth; i++) {
		for (j = 0; j < vsp; j++) {
			imgout[0][i][j] = 0;
			imgout[1][i][j] = 128;
			imgout[2][i][j] = 128;
		}
	}
	for (i = 0; i < hsp; i++) {
		for (j = vsp; j < ptr->biHeight; j++) {
			imgout[0][i][j] = 0;
			imgout[1][i][j] = 128;
			imgout[2][i][j] = 128;
		}
	}
}
