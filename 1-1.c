#include <stdio.h>
#include <stdlib.h>

#define FILENAME "testcp.bmp"

int
main(void)
{
	int i;
	unsigned char c;
	int size;
	FILE *fp;

	fp = fopen(FILENAME, "r");
	if (!fp) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	size = 0;
	while ((fscanf(fp, "%c", &c)) != EOF) {
		printf("%d\n", c);
		size++;
	}

	printf("Size: %d byte\n", size);

	return 0;
}
