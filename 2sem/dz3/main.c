#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main(void) {
    char word[N];
    int res = search("1.txt", word);
    switch (res)
    {
    case -1:
        perror("File open error");
        return 0;
    case -2:
        perror("File reading error");
        return 0;
    default:
        printf("Res: %d\n", res);
        pr(word);
        return 0;
    }
}
