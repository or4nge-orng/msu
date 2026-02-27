#include <stdio.h>
#include <stdlib.h>


int main(void) {

    int n_new = 10, left, right;
    for(int i = 0; i < n_new; i++) {
        left = right = i + 1;
        for (; right < n_new; right++) {
            if (!cmp(a[i], a[right])) {
                swap(&a[left], &a[right]);
                left++;
            }
        }
    }
    return 0;
}
