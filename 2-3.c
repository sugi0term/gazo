#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 100
#define LENGTH 1024

FILE *
xfopen(char *, char *);

int
main(void)
{
	unsigned char ary[BUFSZ];
	FILE *rfp, *wfp;
	int i, idx;
	char sfn[LENGTH], dfn[LENGTH];

	printf("src filename: ");
	scanf("%s", sfn);
	printf("dst filename: ");
	scanf("%s", dfn);

	rfp = xfopen(sfn, "r");

	idx = 0;
	while ((fscanf(rfp, "%c", &ary[idx])) != EOF) {
		idx++;
	}

	printf("Data count: %d\n", idx);
	for (i = 0; i < idx; i++)
		printf("ary[%d] = %d\n", i, ary[i]);
	
	wfp = xfopen(dfn, "w");

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
