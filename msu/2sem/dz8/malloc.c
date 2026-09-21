#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "walloc.h"
//------------------------------------
#define NMEM 1000000000
#define NMEMptr 1000000
typedef struct SMEM_
{void *ptr; int l,l0;}SMEM;
char MEM[NMEM];
SMEM MEMptr[NMEMptr]; int nMEMptr=0;
int WCheckMemCleaning(void);
void MEMCheckLastPtrs(void);
void myCleanupFun (void) __attribute__ ((destructor));
void myCleanupFun (void)
{
 WCheckMemCleaning();
}
//------------------------------------
void *realloc(void *buf,size_t n) 
{
 void *p;int i,l0;
 int n0=n;
 n=(n+3)/4*4;
 if(buf==NULL)
  return malloc(n);
 for(i=0;i<nMEMptr;i++)
 {
  if(MEMptr[i].ptr==buf)
  {
   l0=MEMptr[i].l0;
   if(MEMptr[i].l>=(int)n)
   {
    MEMptr[i].l=n;
    MEMptr[i].l0=n0;
    return MEMptr[i].ptr;
   }
   else
   {
    p=malloc(n);
    memcpy(p,buf,l0);
    free(MEMptr[i].ptr);
    return p;
   }
  }
 }
 printf("Incorrect pointer in realloc().Can't reallocate memory.\n");
 return NULL;
}
//------------------------------------
void *calloc(size_t n,size_t size) 
{
 void *p;
 p=malloc(size*n);
 memset(p,0,size*n);
 return p;
}
//------------------------------------
void *malloc(size_t n) 
{void *ptr=MEM; int i;
 int n0=n;
// printf("Malloc (%d %d)\n",(int)n,nMEMptr);
 n=(n+3)/4*4;
 for(i=0;i<nMEMptr;i++)
 {
  if(MEMptr[i].ptr!=NULL && MEMptr[i].l>0)
  {
   if( (size_t)(((char*)(MEMptr[i].ptr))-(char*)ptr)>=n)
   {
    if(i>0&&MEMptr[i-1].ptr==NULL)
    {
     MEMptr[i-1].ptr=ptr;
     MEMptr[i-1].l=n;
     MEMptr[i-1].l0=n0;
     return ptr;
    }
    else
    {int j;
     for(j=nMEMptr;j>i;j--)
      MEMptr[j]=MEMptr[j-1];
     nMEMptr++;
     MEMptr[i].ptr=ptr;
     MEMptr[i].l=n;
     MEMptr[i].l0=n0;
     return ptr;
    }
   }
   else //if(MEMptr[i].ptr-ptr)>=n)
   {
    ptr=((char*)MEMptr[i].ptr)+MEMptr[i].l;
   }
  }
 }
 MEMptr[nMEMptr].ptr=ptr;
 MEMptr[nMEMptr].l=n;
 MEMptr[nMEMptr].l0=n0;
 nMEMptr++;
return ptr;
return NULL;
}

void MEMCheckLastPtrs(void)
{
 int i;
 for(i=nMEMptr-1;i>=0;i--)
  if(MEMptr[i].ptr==NULL)
  {MEMptr[i].l=MEMptr[i].l0=0; nMEMptr=i;}
  else
   break;
}

void free(void *ptr) 
{int i;if(ptr==NULL)return;
 for(i=0;i<nMEMptr;i++)
  if(MEMptr[i].ptr==ptr)
  {MEMptr[i].ptr=NULL; MEMptr[i].l=MEMptr[i].l0=0;break;}
 MEMCheckLastPtrs();
//printf("Free\n");
}
int WCheckMemCleaning(void)
{
 MEMCheckLastPtrs();
 if(nMEMptr>0)
 {int i,nbad=0,SetBad=0;
  i=0; 
   if(MEMptr[i].ptr!=NULL)//&&MEMptr[i].l0!=16)
   {
    //SetBad=1;
    //nbad++;
   }
  i=1; 
   if(MEMptr[i].ptr!=NULL)//&&MEMptr[i].l0!=46)
   {
    //SetBad=1;
    //nbad++;
   }
  for(i=2;i<nMEMptr;i++)
  {
   if(MEMptr[i].ptr!=NULL)
   {
    SetBad=1;
    nbad++;
   }
  }
  if(SetBad)
   printf("WCheckMemCleaning: memory leaks:\n");
  else
  {
   printf("No memory leaks\n");
   return 0;
  }
  i=0; nbad=0;
   if(MEMptr[i].ptr!=NULL)//&&MEMptr[i].l0!=16)
   {
    //printf("block addr=%p (length=%d)\n",MEMptr[i].ptr,MEMptr[i].l0);
    //nbad++;
   }
  i=1; 
   if(MEMptr[i].ptr!=NULL)//&&MEMptr[i].l0!=46)
   {
    //printf("block addr=%p (length=%d)\n",MEMptr[i].ptr,MEMptr[i].l0);
    //nbad++;
   }
  for(i=2;i<nMEMptr;i++)
  {
   if(MEMptr[i].ptr!=NULL)
   {
    printf("%d)block addr=%p (length=%d)\n",i,MEMptr[i].ptr,MEMptr[i].l0);
    nbad++;
   }
  }
  return nbad;
 }
 else
 {
  printf("WCheckMemCleaning: OK\n");
  return 0;
 }
}

/*
int main(int n,const char **v)
{n=n;v=v;
 {
 char *p0=new char[3];
  printf("p0=%d\n",p0);	
 char *p1=new char[3];
  printf("p1=%d\n",p1);	
 delete p0;
 delete p1;
 }
 {
 char *p0=new char[3];
  printf("p0=%d\n",p0);	
 char *p1=new char[3];
  printf("p1=%d\n",p1);	
  p0=(char*)realloc(p0,100);
 delete p0;
 delete p1;
 }
 {
  FILE *f;
  f=fopen("t.t","w");
  fprintf(f,"Hello!!!\n");
 }
 WCheckMemCleaning();
	return 0;
}
*/