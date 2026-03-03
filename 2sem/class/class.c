#include<stdio.h> //удалить из массива числа, для кот. есть близкие им
//удаляются все копии
#include<stdlib.h>
#include<time.h>
int cmp(int, int);
int cmp(int a, int b){  //а близко b
	if(abs(a-b)<=1)
		return 1; 
	return 0;
}
int main(void){ 
	int n=11, a[n], ind[n],
	left,right,n_int = 0, k = 0;
	srand(time(NULL)); 
	for(int i=0;i<n;i++){a[i]=rand()%11; printf("%d ",a[i]);}
    for(int i = 0; i < n; i++) ind[n_int++] = i;

	for (int i = 0; i <n_int; i++) {
        int flag = 0;
        for (int j = 0; j<n; j++) {
            if (ind[i] != j && cmp(a[j],a[ind[i]])) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) ind[i] = -1;  
    }

    for (left = 0, right = 0; right < n_int; right++) {
        if (ind[right] != -1) {
            ind[left++] = ind[right];
        }
    }
    n_int = left;

    for (left = 0, right = 0; right < n; right++) {
        if ((k < n_int) && (ind[k] = right)) {
            k++; continue;
        }
        a[left++]=a[right];
    }
    n = left;
	puts("\nres");
	for(int i=0;i<n;i++)printf("%d ",a[i]);
	puts("\n");

	return 0;
} 
