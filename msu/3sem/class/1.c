#include <stdio.h>
#include <string.h>

#define N 512

void pr(char *);
int search(const char *SInputFile, char *word);

int search(const char *SInputFile, char *word) {
    FILE *file = fopen(SInputFile, "r");
    char line[N+1], best_word[N] = "", *words;
    int c = 0, best_len = 0, len;
    if (!file) return -1;
    while(fgets(line, sizeof(line), file) != NULL) {
        words = strtok(line, " \t");
        while (words) {
            ++c;
            len = strlen(words);
            if (len > best_len) {
                best_len = len;
                strcpy(best_word, words);
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
    printf("word: ");
    for (char *i = word; *i; i++) {
        putchar(*i);
    }
    putchar('\n');
}

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
        pr(word);
        return 0;
    }
}
