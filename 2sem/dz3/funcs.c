#include "funcs.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int search(const char *SInputFile, char *word) {
    FILE *file = fopen(SInputFile, "r");
    char line[N+1], best_word[N] = "", *words;
    int c = 0, best_len = N+1, only_letters, has_upper, len;
    if (!file) return -1;
    while(fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0;
        words = strtok(line, " \t");
        while (words) {
            only_letters = 1;
            has_upper = 0;
            for(char *i = words; *i; i++) {
                if(!isalpha(*i)) {only_letters = 0; break;}
                if(isupper(*i)) has_upper = 1;
            }
            if (only_letters && has_upper) {
                ++c;
                len = strlen(words);
                if (len <= best_len) {
                    best_len = len;
                    strcpy(best_word, words);
                }
            }
            words = strtok(NULL, " \t");
        }
    }
    if (ferror(file)) {
        fclose(file);
        return -2;
    }
    fclose(file);
    if (c > 0) strcpy(word, best_word);
    return c;
}

void pr(char *word) {
    for (char *i = word; *i; i++) {
        putchar(*i);
    }
    putchar('\n');
}
