#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stack>
#include "wallocC.h"
using namespace std;
int main(void)
{
 {printf("1\n");
 int *p=new int[4];
printf("1\n");
 int *q=new int[8];
printf("1\n");
 int *r=new int[16];
printf("1\n");
 delete[] p;
printf("1\n");
 delete[] r;
printf("1\n");
 q=q;         printf("1\n");
 //delete[] q;  printf("1\n");
 }printf("---\n");
// for(int i=0;i<NMAX;i++)if(used[i])printf("memory leak:<%s>#%d: %d\n",sf[i],il[i],np[i]);
return 0;
}
