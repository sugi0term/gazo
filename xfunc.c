#include <stdio.h>
#include <stdlib.h>

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

void *
xmalloc(size_t size)
{
	void *buf;
	buf = malloc(size);
	if (!buf) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return buf;
}

void *
realloc(void *ptr, size_t size)
{
	void *tmp;
	tmp = realloc(ptr, size);
	if (!tmp) {
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	return tmp;
}
