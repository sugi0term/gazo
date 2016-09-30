#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 1024

int
main(void)
{
	int i;
	unsigned char c;
	int size;
	FILE *fp;
	char fn[BUFSZ];

	printf("filename: ");
	scanf("%s", fn);

	fp = fopen(fn, "r");
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
