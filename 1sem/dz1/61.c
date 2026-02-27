#include <stdio.h>

int task(FILE *, int *);
int main(void) {
    FILE *in = fopen("1.txt", "r");
    int res, err = task(in, &res);
    if (err == 0) {
        printf("File didn't open\n");
        return -1;
    }
    if (err == 1) {
        printf("File is empty\n");
    }
    if (err == 2) {
        printf("File is bad\n");
    }
    if (err == 3) {
        printf("Result = %d\n", res);
    }
    if (in) fclose(in);
    return 0;
}

int task(FILE *in, int *res) {
    int cur, n = 0;
    *res = 0;
    
    if (in == NULL) {
        return 0;
    }
    
    if (fscanf(in, "%d", &cur) == 1) {
        do {
            
            switch(n) {
                case 0: 
                    if (cur == -1) n = 1; 
                    break;
                case 1: 
                    if (cur == -2) n = 2; 
                    else if (cur != -1) n = 0;
                    break;
                case 2: 
                    if (cur == 0) n = 3; 
                    else if (cur == -1) n = 1; 
                    else n = 0;
                    break;
                case 3: 
                    if (cur == -1) n = 4; 
                    else n = 0;
                    break;
                case 4: 
                    if (cur == -2) n = 5; 
                    else if (cur == -1) n = 1; 
                    else n = 0;
                    break;
                case 5: 
                    if (cur == -3) { 
                        (*res)++; 
                        n = 0; 
                    } 
                    else if (cur == -1) n = 1; 
                    else if (cur == 0) n = 3;
                    else n = 0;
                    break;
            }
            printf("%d %d\n", cur, n);
        } while (fscanf(in, "%d", &cur) == 1);
    } else {
        if (feof(in)) return 1;
        else return 2;
    }
    if (!feof(in)) return 2;
    return 3;
}
