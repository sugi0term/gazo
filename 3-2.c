#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "xfunc.h"

#define HEADER_LENGTH 54
#define SIZE 512

void
get_data();
void
processing();

uint8_t header[HEADER_LENGTH];
uint8_t imgin[3][SIZE][SIZE];
bmp_t *ptr;
int alignment;

int
main(void)
{
	get_data();
	processing();

	return 0;
}

void
get_data()
{
	FILE *fp;
	int c;
	int i, j, k, idx;
	char fn[FILENAME_MAX];

	int blockSize[] = {
		2, 4, 4, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 4, 4
	};

	char *blockLabel[] = {
		"ファイルタイプ", "ファイルサイズ", "予約領域", "オフセット",
		"情報ヘッダサイズ", "画像の幅", "画像の高さ", "色プレーン数",
		"１画素当たりのビット数", "圧縮方式", "画像データサイズ",
		"水平解像度", "垂直解像度", "色数", "重要な色数"
	};

	ptr = (bmp_t *)header;

	printf("filename: ");
	scanf("%s", fn);

	fp = xfopen(fn, "r");

	for (i = 0; i < HEADER_LENGTH; i++) {
		header[i] = fgetc(fp);
	}

	for (i = ptr->biHeight - 1; 0 <= i; i--) {
		for (j = 0; j < ptr->biWidth; j++) {
			for (k = 2; 0 <= k; k--) {
				imgin[k][i][j] = fgetc(fp);
			}
		}
	}

	idx = 0;
	for (i = 0; i < sizeof(blockLabel) / sizeof(char *); i++) {
		printf("＜%s＞\n", blockLabel[i]);
		for (j = 0; j < blockSize[i]; j++) {
			printf("header[%d] = %02x\n", idx, header[idx]);
			idx++;
		}
		printf("\n");
	}

	puts("＜挿入ビット数＞");
	alignment = ptr->bfSize - ptr->bfOffBits - ptr->biWidth * ptr->biHeight * (ptr->biBitCount / 8); 
	printf("%d\n", alignment);
	printf("\n");
	
}

void
processing()
{
	int i, j, k;
	char *blockLabel[] = {
		"＜Ｒ信号＞", "＜Ｇ信号＞", "＜Ｂ信号＞"
	};

	for (k = 0; k < 3; k++) {
		puts(blockLabel[k]);
		for (i = 0; i < ptr->biHeight; i++) {
			for (j = 0; j < ptr->biWidth; j++) {
				printf("%02x ", imgin[k][i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
}
