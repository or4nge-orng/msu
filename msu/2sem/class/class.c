#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(void) {

    FILE *file = fopen("1.txt", "r");
    char fuf[512];

    while (fgets(fuf, 512, file) != NULL) {
        puts(fuf);
    }

    return 0;
}
