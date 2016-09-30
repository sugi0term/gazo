#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "xfunc.h"

#define HEADER_LENGTH 54

void
get_data();

uint8_t header[HEADER_LENGTH];

int
main(void)
{
	get_data();

	return 0;
}

void
get_data()
{
	FILE *fp;
	int i, j, idx;
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

	bmp_t *ptr = (bmp_t *)header;

	printf("filename: ");
	scanf("%s", fn);

	fp = xfopen(fn, "r");

	for (i = 0; i < sizeof(header) / sizeof(uint8_t); i++) {
		header[i] = fgetc(fp);
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
	printf("%u\n", ptr->bfSize - ptr->bfOffBits - 
		ptr->biWidth * ptr->biHeight * (ptr->biBitCount / 8));
	printf("\n");

	printf("bfSize: %u\n", ptr->bfSize);
	printf("bfOffBits: %u\n", ptr->bfOffBits);
	printf("biWidth: %u\n", ptr->biWidth);
	printf("biHeight: %u\n", ptr->biHeight);
	printf("biBitCount: %u\n", ptr->biBitCount);
	printf("\n");
	// printf("bfSize: %d\n", *((int *)&header[2]));
	// printf("bfSize: %d\n", header[2] + (header[3] << 8) + (header[4] << 16) + (header[5] << 24));
}
