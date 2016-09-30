#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define READFILE "test.bmp"
#define WRITEFILE "testcp.bmp"

FILE *
xfopen(char *, char *);

int
main(void)
{
	unsigned char ary[SIZE];
	FILE *rfp, *wfp;
	int i, idx;

	rfp = xfopen(READFILE, "r");

	idx = 0;
	while ((fscanf(rfp, "%c", &ary[idx])) != EOF) {
		idx++;
	}

	printf("Data count: %d\n", idx);
	for (i = 0; i < idx; i++)
		printf("ary[%d] = %d\n", i, ary[i]);
	
	wfp = xfopen(WRITEFILE, "w");

	for (i = 0; i < idx; i++)
		fprintf(wfp, "%c", ary[i]);

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
