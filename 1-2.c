#include <stdio.h>
#include <stdlib.h>

#define FILENAME "testcp.bmp"

int
main(void)
{
	int i;
	int n;
	int d;
	FILE *fp;

	fp = fopen(FILENAME, "w");
	if (!fp) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	printf("Byte: ");
	scanf("%d", &n);
	getchar();

	for (i = 0; i < n; i++) {
		printf("No.%d: ", i + 1);
		scanf("%d", &d);
		fprintf(fp, "%c", d);
	}

	return 0;
}
