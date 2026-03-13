#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(void) {

    FILE *file = fopen("1.txt", "r");
    char fuf[512];

    while (fscanf(file, "%s", fuf))

    return 0;
}