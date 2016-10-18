#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "bmp.h"
#include "xfunc.h"

#define HEADER_LENGTH 54

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

char *ybrLabel[] = {
	"Ｙ信号", "Ｃｂ信号", "Ｃｒ信号"
};
char *rgbLabel[] = {
	"Ｒ信号", "Ｇ信号", "Ｂ信号"
};

uint8_t header[HEADER_LENGTH];
uint8_t imgin[3][512][512];
uint8_t imgout[3][512][512];
bmp_t *ptr;
int alignment;

void
getData(void);
void
rgbToYbr(void);
void
processing(void);
void
ybrToRgb(void);
void
putData(void);

int
main(int argc, char **argv)
{
	getData();
	rgbToYbr();
	processing();
	ybrToRgb();
	putData();

	return 0;
}

void
getData()
{
	FILE *fp;
	char fn[FILENAME_MAX];
	char *label[] = {
		"ファイルサイズ", "オフセット", "画像の幅",
		"画像の高さ", "１画素あたりのビット数", "挿入ビット数"
	};
	int data[sizeof(label) / sizeof(char *)];
	int i, j, k;

	printf("input filename: ");
	scanf("%s", fn);
	printf("\n");

	fp = xfopen(fn, "r");
	fread(header, HEADER_LENGTH, 1, fp);
	ptr = (bmp_t *)header;

	alignment = ptr->bfSize - ptr->bfOffBits - ptr->biWidth * ptr->biHeight * (ptr->biBitCount / 8);
	data[0] = ptr->bfSize;
	data[1] = ptr->bfOffBits;
	data[2] = ptr->biWidth;
	data[3] = ptr->biHeight;
	data[4] = ptr->biBitCount;
	data[5] = alignment;

	for (i = 0; i < sizeof(label) / sizeof(char *); i++) {
		printf("＜%s＞\n", label[i]);
		printf("%u\n", data[i]);
	}

	for (i = ptr->biHeight - 1; 0 <= i; i--) {
		for (j = 0; j < ptr->biWidth; j++) {
			for (k = 2; 0 <= k; k--) {
				imgin[k][i][j] = fgetc(fp);
			}
		}
	}
	printf("\n");
}

void rgbToYbr()
{
	int i, j, k, m, n;
	double rgb[3] = {};
	double ycbcr[3] = {};

	puts("入力信号（ＲＧＢ）：");
	for (k = 0; k < 3; k++) {
		printf("＜%s＞\n", rgbLabel[k]);
		for (i = 0; i < ptr->biHeight; i++) {
			for (j = 0; j < ptr->biWidth; j++) {
				printf("%02x ", imgin[k][i][j]);
			}
			printf("\n");
		}
		printf("\n");	
	}

	for (m = 0; m < ptr->biHeight; m++) {
		for (n = 0; n < ptr->biWidth; n++) {
			for (k = 0; k < 3; k++) {
				rgb[k] = imgin[k][m][n];
				ycbcr[k] = 0;
			}
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
					ycbcr[i] += toYcbcr[i][j] * rgb[j];
				}
			}

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
			for (k = 0; k < 3; k++) {
				imgin[k][m][n] = ycbcr[k];
			}
		}
	}
	puts("入力信号（ＹＣｂＣｒ）：");
	for (k = 0; k < 3; k++) {
		printf("＜%s＞\n", ybrLabel[k]);
		for (i = 0; i < ptr->biHeight; i++) {
			for (j = 0; j < ptr->biWidth; j++) {
				printf("%02x ", imgin[k][i][j]);
			}
			printf("\n");
		}
		printf("\n");	
	}
}

void processing()
{
	int i, j, k;

	for (k = 0; k < 3; k++) {
		for (i = 0; i < ptr->biHeight; i++) {
			for (j = 0; j < ptr->biWidth; j++) {
				imgout[k][i][j] = imgin[k][i][j];
			}
		}
	}
}

void ybrToRgb()
{
	int i, j, k, m, n;
	double rgb[3] = {};
	double ycbcr[3] = {};

	puts("出力信号（ＹＣｂＣｒ）：");
	for (k = 0; k < 3; k++) {
		printf("＜%s＞\n", ybrLabel[k]);
		for (i = 0; i < ptr->biHeight; i++) {
			for (j = 0; j < ptr->biWidth; j++) {
				printf("%02x ", imgout[k][i][j]);
			}
			printf("\n");
		}
		printf("\n");	
	}
	for (m = 0; m < ptr->biHeight; m++) {
		for (n = 0; n < ptr->biWidth; n++) {
			for (k = 0; k < 3; k++) {
				ycbcr[k] = imgout[k][m][n];
				rgb[k] = 0;
			}

			for (i = 1; i < 3; i++) {
				ycbcr[i] -= 128;
			}

			for (i = 0; i < 3; i++) {
				rgb[i] = 0;
				for (j = 0; j < 3; j++) {
					rgb[i] += toRgb[i][j] * ycbcr[j];
				}
			}

			for (i = 0; i < 3; i++) {
				rgb[i] = round(rgb[i]);
			}
			for (i = 0; i < 3; i++) {
				if (255 < rgb[i]) rgb[i] = 255;
				if (rgb[i] < 0) rgb[i] = 0;
			}
			for (k = 0; k < 3; k++) {
				imgout[k][m][n] = rgb[k];
			}
		}
	}

	puts("出力信号（ＲＧＢ）：");
	for (k = 0; k < 3; k++) {
		printf("＜%s＞\n", rgbLabel[k]);
		for (i = 0; i < ptr->biHeight; i++) {
			for (j = 0; j < ptr->biWidth; j++) {
				printf("%02x ", imgout[k][i][j]);
			}
			printf("\n");
		}
		printf("\n");	
	}
}

void
putData(void)
{
	int i, j, k;
	char fn[FILENAME_MAX];
	FILE *fp;

	printf("dst filename: ");
	scanf("%s", fn);

	fp = xfopen(fn, "w");

	for (i = 0; i < HEADER_LENGTH; i++) {
		fputc(header[i], fp);
	}
	for (i = ptr->biHeight - 1; 0 <= i; i--) {
		for (j = 0; j < ptr->biWidth; j++) {
			for (k = 2; 0 <= k; k--) {
				putc(imgin[k][i][j], fp);
			}
		}
	}
	for (i = 0; i < alignment; i++) {
		fputc(0x00, fp);
	}
}
