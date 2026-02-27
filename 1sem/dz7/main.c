#include "funcs.h"
int main(void) {
    FILE *in = fopen("1.txt", "r");
    size_t n;
    int *mass = NULL, err = read(in, &mass, &n);
    if (err) fclose(in);
    switch(err){
		case 0:	printf("No file\n");break;
		case -1:printf("Bad file\n");break;
		case -2: printf("Empty file\n");break;
        case -3: printf("Bad size\n");break;
		default: 
            puts("Begin");
            pr(mass,n);
            puts("Answer");
            n = task(mass, n);
            pr(mass,n);
            free(mass);
    }
    return 0;
}