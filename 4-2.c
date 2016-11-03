#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
	char *label[3] = {
		"R", "G", "B"
	};
	int i, j;

	printf("\n");
	puts("＜信号値を入力してください（整数値）＞");
	for (i = 0; i < sizeof(label) / sizeof(char *); i++) {
		printf("%s: ", label[i]);
		scanf("%lf", &rgb[i]);
	}
	printf("\n");

	puts("入力されたＲＧＢ信号（整数値）＞");
	for (i = 0; i < 3; i++) {
		printf("%s: %3.4f\n", label[i], rgb[i]);
	}
	printf("\n");

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			ycbcr[i] += toYcbcr[i][j] * rgb[j];
		}
	}

	puts("変換されたＹＣｂＣｒ信号（実数値）＞");
	for (i = 0; i < 3; i++) {
		printf("%s: %3.4f\n", label[i], ycbcr[i]);
	}
	printf("\n");

	for (i = 0; i < 3; i++) {
		ycbcr[i] = round(ycbcr[i]);
	}
	for (i = 1; i < 3; i++) {
		ycbcr[i] += 128;
	}
	for (i = 0; i < 3; i++) {
		if (255 < ycbcr[i]) ycbcr[i] = 255;
		if (ycbcr[i] < 0) ycbcr[i] = 0;
	}
	puts("変換されたＹＣｂＣｒ信号（整数値）＞");
	for (i = 0; i < 3; i++) {
		printf("%s: %3d\n", label[i], (int)ycbcr[i]);
	}
	printf("\n");

	for (i = 1; i < 3; i++) {
		ycbcr[i] -= 128;
	}

	for (i = 0; i < 3; i++) {
		rgb[i] = 0;
		for (j = 0; j < 3; j++) {
			rgb[i] += toRgb[i][j] * ycbcr[j];
		}
	}

	puts("再度変換されたＲＧＢ信号（実数値）＞");
	for (i = 0; i < 3; i++) {
		printf("%s: %3.4f\n", label[i], rgb[i]);
	}
	printf("\n");

	for (i = 0; i < 3; i++) {
		rgb[i] = round(rgb[i]);
	}
	for (i = 0; i < 3; i++) {
		if (255 < rgb[i]) rgb[i] = 255;
		if (rgb[i] < 0) rgb[i] = 0;
	}
	puts("再度変換されたＲＧＢ信号（整数値）＞");
	for (i = 0; i < 3; i++) {
		printf("%s: %3d\n", label[i], (int)rgb[i]);
	}
	printf("\n");

	return 0;
}
