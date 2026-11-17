#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "walloc.h"
int nMEMptr=0;
//void CheckNewDeleteC(void);
int main(int argc,const char **argv)
{char **p;int OK=1,*nalloc,np=10000,nc=0,i,nmem,nmemmax=100,MemTotal=0;
 argc=argc;argv=argv;
 p=new char*[(i=np*sizeof(char*))]; MemTotal+=i;
 nalloc=new int[(i=np*sizeof(int))]; MemTotal+=i;
 memset(p,0,np*sizeof(char*));
 memset(nalloc,0,np*sizeof(int));
 for(nc=0;OK&&nc<100000;nc++)
 {//printf("nc=%d\n",nc);
  i=rand()%np;
  if(p[i])
  {
   delete[] (p[i]);
   p[i]=NULL;
   MemTotal-=nalloc[i];
  }
  else
  {
   nmem=1+rand()%nmemmax;
   nalloc[i]=nmem;
   MemTotal+=nmem;
   p[i]=new char[nmem];
   if(p[i]==NULL)OK=0;
  }
  if(nc%10000==0)
  printf("nc=%d MemTotal=%d nMEMptr=%d\n",nc,MemTotal,nMEMptr);
 }
 for(i=0;i<np;i++)
  if(p[i])delete[] (p[i]);
 delete[] (p);delete[] (nalloc);
//  WCheckMemCleaning();
return 0;
}
