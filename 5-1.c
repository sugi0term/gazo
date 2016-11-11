#include "iip.h"

void
flipImg(void);

int
main(int argc, char **argv)
{
	getData(argv[1]);
	rgbToYbr();
	flipImg();
	ybrToRgb();
	putData(argv[2]);

	return 0;
}

void
flipImg(void)
{
	int i, j, k;
	
	for (i = 0; i < ptr->biWidth; i++) {
		for (j = 0; j < ptr->biHeight; j++) {
			for (k = 0; k < 3; k++) {
				imgout[k][i][j] = imgin[k][ptr->biWidth - i][j];
			}
		}
	}
}
