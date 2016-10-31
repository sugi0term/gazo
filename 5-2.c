#include <stdio.h>
#include "iip.h"

void
monoImg(void);

int
main(int argc, char **argv)
{
	getData();
	rgbToYbr();
	monoImg();
	ybrToRgb();
	putData();

	return 0;
}

void
monoImg(void)
{
	int i, j, k;
	char *label[] = {
		"Y", "Cb", "Cr"
	};
	int mode[3];

	puts("Copy => 1, Replace to 128 => 0");
	for (i = 0; i < sizeof(label) / sizeof(char *); i++) {
		printf("%2s: ", label[i]);
		scanf("%d", &mode[i]);
	}
	
	for (i = 0; i < ptr->biWidth; i++) {
		for (j = 0; j < ptr->biHeight; j++) {
			for (k = 0; k < 3; k++) {
				if (mode[k] == 1) {
					imgout[k][i][j] = imgin[k][i][j];
				}
				else {
					imgout[k][i][j] = 128;
				}
			}
		}
	}
}
