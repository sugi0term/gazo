#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 100
#define LENGTH 1024

FILE *
xfopen(char *, char *);

int
main(void)
{
	FILE *fp1, *fp2;
	char fn1[LENGTH], fn2[LENGTH];
	int c1, c2;

	printf("fn1: ");
	scanf("%s", fn1);
	printf("fn2: ");
	scanf("%s", fn2);

	fp1 = xfopen(fn1, "r");
	fp2 = xfopen(fn2, "r");

	while ((c1 = fgetc(fp1)) == (c2 = fgetc(fp2))) {
		if (c1 == EOF && c2 == EOF) {
			printf("%s と %s は等しいです\n", fn1, fn2);
			exit(0);
		}
	}

	printf("%s と %s は異なります\n", fn1, fn2);
	return 0;
}

FILE *
xfopen(char *filename, char *mode)
{
	FILE *fp;

	fp = fopen(filename, mode);
	if (!fp) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	return fp;
}
