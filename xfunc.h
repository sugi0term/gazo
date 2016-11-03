#ifndef _XFUNC_H_
#define _XFUNC_H_

#include <stdio.h>

FILE *
xfopen(char *, char *);
void *
xmalloc(size_t);
void *
xrealloc(void *, size_t);

#endif
