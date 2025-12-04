#include <stdio.h>
#include <stdlib.h>

void pr(int [], size_t);
void sort(int [], size_t, int (const void *, const void *));
void generate_array(int **, size_t);
void copy_array(int *, int **, size_t);
int compare(const void *a, const void *b);
void swap(int *, int *);