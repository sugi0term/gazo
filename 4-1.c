#include <stdio.h>
#include <stdlib.h>
#include "xfunc.h"

int
main(void)
{
	double toYcbcr[][3] = {
		{0.2990, 0.5870, 0.1140},
		{-0.1687, -0.3313, 0.5000},
		{0.5000, -0.4187, -0.0813}
	};
	double toRgb[][3] = {
		{1.0000, 0.0000, 1.4020},
		{1.0000, -0.3441, -0.7141},
		{1.0000, 1.7720, 0.0000}
	};
	double ycbcr[3] = {};
	double rgb[3] = {};
	char *rgbLabel[3] = {
		"R", "G", "B"
	};
	char *ycbcrLabel[3] = {
		"Y", "Cb", "Cr"
	};
	int i, j;

	printf("\n");
	puts("＜信号値を入力してください（実数値）＞");
	for (i = 0; i < sizeof(rgbLabel) / sizeof(char *); i++) {
		printf("%s: ", rgbLabel[i]);
		scanf("%lf", &rgb[i]);
	}
	printf("\n");

	puts("入力されたＲＧＢ信号（実数値）＞");
	for (i = 0; i < 3; i++) {
		printf("%s: %3.4f\n", rgbLabel[i], rgb[i]);
	}
	printf("\n");

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			ycbcr[i] += toYcbcr[i][j] * rgb[j];
		}
	}
	
	puts("変換されたＹＣｂＣｒ信号（実数値）＞");
	for (i = 0; i < 3; i++) {
		printf("%s: %3.4f\n", ycbcrLabel[i], ycbcr[i]);
	}
	printf("\n");

	for (i = 0; i < 3; i++) {
		rgb[i] = 0;
		for (j = 0; j < 3; j++) {
			rgb[i] += toRgb[i][j] * ycbcr[j];
		}
	}
	
	puts("再度変換されたＲＧＢ信号（実数値）＞");
	for (i = 0; i < 3; i++) {
		printf("%s: %3.4f\n", rgbLabel[i], rgb[i]);
	}
	printf("\n");

	return 0;
}
