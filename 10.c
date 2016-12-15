#include <stdio.h>
#include <string.h>
#include "iip.h"
#include "10.h"

void
binarization(uint8_t imgData[][SIZE][SIZE])
{
	int x, y;
	uint8_t tmp[nColors][SIZE][SIZE];

	for (x = 0; x < imgHdr->biWidth; x++) {
		for (y = 0; y < imgHdr->biHeight; y++) {
			if (T <= imgData[Y][x][y]) {
				tmp[Y][x][y] = 255;
			}
			else {
				tmp[Y][x][y] = 0;
			}
			tmp[Cb][x][y] = 128;
			tmp[Cr][x][y] = 128;
		}
	}
	memcpy(imgData, tmp, nColors * SIZE * SIZE);
}

void
contraction(uint8_t imgData[][SIZE][SIZE])
{
	int x, y;
	uint8_t tmp[nColors][SIZE][SIZE];

	for (x = 0; x < imgHdr->biWidth; x++) {
		for (y = 0; y < imgHdr->biHeight; y++) {
			if (imgData[Y][x][y] == BLACK && exists(imgData, x, y, WHITE)) {
				tmp[Y][x][y] = WHITE;
			}
			else {
				tmp[Y][x][y] = imgData[Y][x][y];
			}
			tmp[Cb][x][y] = imgData[Cb][x][y];
			tmp[Cr][x][y] = imgData[Cr][x][y];
		}
	}
	memcpy(imgData, tmp, nColors * SIZE * SIZE);
}

void
expansion(uint8_t imgData[][SIZE][SIZE])
{
	int x, y;
	uint8_t tmp[nColors][SIZE][SIZE];

	for (x = 0; x < imgHdr->biWidth; x++) {
		for (y = 0; y < imgHdr->biHeight; y++) {
			if (imgData[Y][x][y] == WHITE && exists(imgData, x, y, BLACK)) {
				tmp[Y][x][y] = BLACK;
			}
			else {
				tmp[Y][x][y] = imgData[Y][x][y];
			}
			tmp[Cb][x][y] = imgData[Cb][x][y];
			tmp[Cr][x][y] = imgData[Cr][x][y];
		}
	}
	memcpy(imgData, tmp, nColors * SIZE * SIZE);
}
int
exists(uint8_t imgData[][SIZE][SIZE], int x, int y, int pixel)
{
	int i, j, cnt;
	int tx, ty;

	cnt = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			tx = x + i - 1;
			ty = y + j - 1;
			if (tx < 0 || ty < 0 || imgHdr->biWidth <= tx || imgHdr->biHeight <= ty) {
				continue;
			}
			if (imgData[Y][tx][ty] == pixel) {
				cnt++;
			}
		}
	}
	if (0 < cnt) {
		return 1;
	}
	return 0;
}

void
opening(uint8_t imgData[][SIZE][SIZE], int n)
{
	int i;

	for (i = 0; i < n; i++) {
		contraction(imgData);
	}
	for (i = 0; i < n; i++) {
		expansion(imgData);
	}
}

void
closing(uint8_t imgData[][SIZE][SIZE], int n)
{
	int i;

	for (i = 0; i < n; i++) {
		expansion(imgData);
	}
	for (i = 0; i < n; i++) {
		contraction(imgData);
	}
}

void
printImgInHex(uint8_t imgData[][SIZE][SIZE])
{
	int x, y;
	int xSize, ySize;

	xSize = imgHdr->biWidth;
	ySize = imgHdr->biHeight;
	if (8 < xSize) {
		xSize = 8;
	}
	if (8 < ySize) {
		ySize = 8;
	}
	for (x = 0; x < xSize; x++) {
		for (y = 0; y < ySize; y++) {
			printf("%02X ", imgData[Y][x][y]);
		}
		printf("\n");
	}
}
