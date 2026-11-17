#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stack>
//#include "wallocC.h"
//#undef new
#define NMAX 300000000
#define LMAX 100000
using namespace std;
//---
//#define NMAX 1000
//#define LMAX 100000
//128 512 2048 8192 32768 131072 524288 2097152
char p128[NMAX/128][128];
char p512[NMAX/512][512];
char p8192[NMAX/8192][8192];
char p131072[NMAX/131072][131072];
char p2097152[NMAX/2097152][2097152];
int np128[NMAX/128]={0}; //инициализацция не обязательна
int np512[NMAX/512]={0}; //инициализацция не обязательна
int np8192[NMAX/8192]={0}; //инициализацция не обязательна
int np131072[NMAX/131072]={0}; //инициализацция не обязательна
int np2097152[NMAX/2097152]={0}; //инициализацция не обязательна
char used128[NMAX/128]={0};
char used512[NMAX/512]={0};
char used8192[NMAX/8192]={0};
char used131072[NMAX/131072]={0};
char used2097152[NMAX/2097152]={0};
char sf128[NMAX/128][128]={0};
char sf512[NMAX/512][128]={0};
char sf8192[NMAX/8192][128]={0};
char sf131072[NMAX/131072][128]={0};
char sf2097152[NMAX/2097152][128]={0};
int il128[NMAX/128]={0}; //инициализацция не обязательна
int il512[NMAX/512]={0}; //инициализацция не обязательна
int il8192[NMAX/8192]={0}; //инициализацция не обязательна
int il131072[NMAX/131072]={0}; //инициализацция не обязательна
int il2097152[NMAX/2097152]={0}; //инициализацция не обязательна
void CheckNewDeleteC(void);

static int SetShow=
#ifdef SHOW_MEM_ALLOCATIONS
1;
#else 
0;
#endif

static int SetFirst_CheckNewDeleteC=1;
static int i0Used[5]={0};
void *malloc(size_t n)
{
if(SetFirst_CheckNewDeleteC){atexit (CheckNewDeleteC);SetFirst_CheckNewDeleteC=0;}
char *used=(n<=128?used128:n<=512?used512:n<=8192?used8192:n<=131072?used131072:n<=2097152?used2097152:nullptr);
 int *np=(n<=128?np128:n<=512?np512:n<=8192?np8192:n<=131072?np131072:n<=2097152?np2097152:nullptr);
 int nn=(n<=128?NMAX/128:n<=512?NMAX/512:n<=8192?NMAX/8192:n<=131072?NMAX/131072:n<=2097152?NMAX/2097152:NMAX/2097152);
 int i0=(n<=128?0:n<=512?1:n<=8192?2:n<=131072?3:n<=2097152?4:4);
 if(!used)return nullptr;
 int i=i0Used[i0]; for(i=i0Used[i0];i<nn;i++){if(!used[i])goto l1; } for(i=0;i<i0Used[i0];i++){if(!used[i])goto l1;} return NULL; l1:;i0Used[i0]=i;
 np[i]=n; used[i]=1; 
 if(SetShow)printf("malloc: i=%d size=%d\n",(int)i,(int)n);
 return (n<=128?p128[i]:n<=512?p512[i]:n<=8192?p8192[i]:n<=131072?p131072[i]:n<=2097152?p2097152[i]:nullptr);//p[i];
}
void *malloc(size_t n,const char*sf_,int il_)
{
if(SetFirst_CheckNewDeleteC){atexit (CheckNewDeleteC);SetFirst_CheckNewDeleteC=0;}
char *used=(n<=128?used128:n<=512?used512:n<=8192?used8192:n<=131072?used131072:n<=2097152?used2097152:nullptr);
 int *np=(n<=128?np128:n<=512?np512:n<=8192?np8192:n<=131072?np131072:n<=2097152?np2097152:nullptr);
 int *il=(n<=128?il128:n<=512?il512:n<=8192?il8192:n<=131072?il131072:n<=2097152?il2097152:nullptr);
 int nn=(n<=128?NMAX/128:n<=512?NMAX/512:n<=8192?NMAX/8192:n<=131072?NMAX/131072:n<=2097152?NMAX/2097152:NMAX/2097152);
 int i0=(n<=128?0:n<=512?1:n<=8192?2:n<=131072?3:n<=2097152?4:4);
 if(!used)return nullptr;
// int i=0; while(used[i])i++;
 int i=i0Used[i0]; for(i=i0Used[i0];i<nn;i++){if(!used[i])goto l1; } for(i=0;i<i0Used[i0];i++){if(!used[i])goto l1;} return NULL; l1:;i0Used[i0]=i;
 np[i]=n; used[i]=1; 
 strcpy((n<=128?sf128[i]:n<=512?sf512[i]:n<=8192?sf8192[i]:n<=131072?sf131072[i]:n<=2097152?sf2097152[i]:sf2097152[i]),sf_); 
 il[i]=il_;
 if(SetShow)printf("malloc: i=%d %s #%d size=%d\n",(int)i,sf_,(int)il_,(int)n);
 return (n<=128?p128[i]:n<=512?p512[i]:n<=8192?p8192[i]:n<=131072?p131072[i]:n<=2097152?p2097152[i]:nullptr);//p[i];
//int i=0; while(used[i])i++;
// np[i]=n; used[i]=1; 
// strcpy(::sf[i],sf); ::il[i]=il;
// return p[i];
}

void *calloc(size_t n)
{
if(SetFirst_CheckNewDeleteC){atexit (CheckNewDeleteC);SetFirst_CheckNewDeleteC=0;}
char *used=(n<=128?used128:n<=512?used512:n<=8192?used8192:n<=131072?used131072:n<=2097152?used2097152:nullptr);
 int *np=(n<=128?np128:n<=512?np512:n<=8192?np8192:n<=131072?np131072:n<=2097152?np2097152:nullptr);
 int nn=(n<=128?NMAX/128:n<=512?NMAX/512:n<=8192?NMAX/8192:n<=131072?NMAX/131072:n<=2097152?NMAX/2097152:NMAX/2097152);
 int i0=(n<=128?0:n<=512?1:n<=8192?2:n<=131072?3:n<=2097152?4:4);
 if(!used)return nullptr;
// int i=0; while(used[i])i++;
 int i=i0Used[i0]; for(i=i0Used[i0];i<nn;i++){if(!used[i])goto l1; } for(i=0;i<i0Used[i0];i++){if(!used[i])goto l1;} return NULL; l1:;i0Used[i0]=i;
 void *pp=(n<=128?p128[i]:n<=512?p512[i]:n<=8192?p8192[i]:n<=131072?p131072[i]:n<=2097152?p2097152[i]:nullptr);
 memset(pp,0,n);
 np[i]=n; used[i]=1; 
 if(SetShow)printf("calloc: i=%d size=%d\n",(int)i,(int)n);
 return pp;//p[i];
}
void *calloc(size_t n,const char*sf_,int il_)
{
if(SetFirst_CheckNewDeleteC){atexit (CheckNewDeleteC);SetFirst_CheckNewDeleteC=0;}
char *used=(n<=128?used128:n<=512?used512:n<=8192?used8192:n<=131072?used131072:n<=2097152?used2097152:nullptr);
 int *np=(n<=128?np128:n<=512?np512:n<=8192?np8192:n<=131072?np131072:n<=2097152?np2097152:nullptr);
 int *il=(n<=128?il128:n<=512?il512:n<=8192?il8192:n<=131072?il131072:n<=2097152?il2097152:nullptr);
 int nn=(n<=128?NMAX/128:n<=512?NMAX/512:n<=8192?NMAX/8192:n<=131072?NMAX/131072:n<=2097152?NMAX/2097152:NMAX/2097152);
 int i0=(n<=128?0:n<=512?1:n<=8192?2:n<=131072?3:n<=2097152?4:4);
 if(!used)return nullptr;
// int i=0; while(used[i])i++;
 int i=i0Used[i0]; for(i=i0Used[i0];i<nn;i++){if(!used[i])goto l1; } for(i=0;i<i0Used[i0];i++){if(!used[i])goto l1;} return NULL; l1:;i0Used[i0]=i;
 np[i]=n; used[i]=1; 
 strcpy((n<=128?sf128[i]:n<=512?sf512[i]:n<=8192?sf8192[i]:n<=131072?sf131072[i]:n<=2097152?sf2097152[i]:sf2097152[i]),sf_); 
 il[i]=il_;
 if(SetShow)printf("malloc: i=%d %s #%d size=%d\n",(int)i,sf_,(int)il_,(int)n);
 void *pp=(n<=128?p128[i]:n<=512?p512[i]:n<=8192?p8192[i]:n<=131072?p131072[i]:n<=2097152?p2097152[i]:nullptr);
 memset(pp,0,n);
 return   pp;//p[i];
//int i=0; while(used[i])i++;
// np[i]=n; used[i]=1; 
// strcpy(::sf[i],sf); ::il[i]=il;
// return p[i];
}

#define S(N) ((char*)r>=(char*)p##N && (char*)r<((char*)p##N)+sizeof(p##N))

void *realloc(void *r,size_t n) 
{//char *used=(S(128)?used128:S(512)?used512:S(8192)?used8192:S(131072)?used131072:S(2097152)?used2097152:nullptr);
if(SetFirst_CheckNewDeleteC){atexit (CheckNewDeleteC);SetFirst_CheckNewDeleteC=0;}
 int *np=(S(128)?np128:S(512)?np512:S(8192)?np8192:S(131072)?np131072:S(2097152)?np2097152:nullptr);
 int NMAX_=(S(128)?NMAX/128:S(512)?NMAX/512:S(8192)?NMAX/8192:S(131072)?NMAX/131072:S(2097152)?NMAX/2097152:0);
 int LMAX_=(S(128)?128:S(512)?512:S(8192)?8192:S(131072)?131072:S(2097152)?2097152:0);
// printf("free: NMAX=%d LMAX=%d\n",NMAX_,LMAX_);
 if(NMAX_==0||LMAX_==0){if(0)printf("1)can't free  NMAX=%d LMAX=%d r=%p\n",NMAX_,LMAX_,r);return nullptr;}
 size_t i=((char*)r-(char*)(S(128)?(char*)p128:S(512)?(char*)p512:S(8192)?(char*)p8192:S(131072)?(char*)p131072:S(2097152)?(char*)p2097152:nullptr))/LMAX_; 
 if(SetShow)printf("realloc: i=%d size=%d -> ",(int)i,np[i]);
 void *buf2=malloc(n);
 memcpy(buf2,r,np[i]);
 free(r);
 return buf2;
}

void free(void *r)
{
if(SetFirst_CheckNewDeleteC){atexit (CheckNewDeleteC);SetFirst_CheckNewDeleteC=0;}
char *used=(S(128)?used128:S(512)?used512:S(8192)?used8192:S(131072)?used131072:S(2097152)?used2097152:nullptr);
 int *np=(S(128)?np128:S(512)?np512:S(8192)?np8192:S(131072)?np131072:S(2097152)?np2097152:nullptr);
 int NMAX_=(S(128)?NMAX/128:S(512)?NMAX/512:S(8192)?NMAX/8192:S(131072)?NMAX/131072:S(2097152)?NMAX/2097152:0);
 int LMAX_=(S(128)?128:S(512)?512:S(8192)?8192:S(131072)?131072:S(2097152)?2097152:0);
// printf("free: NMAX=%d LMAX=%d\n",NMAX_,LMAX_);
 if(NMAX_==0||LMAX_==0){if(0)printf("1)can't free  NMAX=%d LMAX=%d r=%p\n",NMAX_,LMAX_,r);return;}
 size_t i=((char*)r-(char*)(S(128)?(char*)p128:S(512)?(char*)p512:S(8192)?(char*)p8192:S(131072)?(char*)p131072:S(2097152)?(char*)p2097152:nullptr))/LMAX_; 
// if(SetShow)printf("free: i=%d size=%d (NMAX=%d LMAX=%d)\n",(int)i,np[i],NMAX_,LMAX_);
 if(SetShow)printf("free: i=%d size=%d\n",(int)i,np[i]);
 if((int)i>=NMAX_){if(0)printf("2)can't free %d\n",(int)i);}
 else if(!used[i])printf("free double\n");
 else {np[i]=0; used[i]=0;}
}
//--
void *operator new(size_t n)
{if(SetShow)printf("new(%d): ",(int)n); return malloc(n);}
void *operator new(size_t n,size_t sz)
{if(SetShow)printf("new(%d,%d): ",(int)n,(int)sz); return malloc(n);}
void *operator new[](size_t n)
{if(SetShow)printf("new[](%d): ",(int)n); return malloc(n);}
void *operator new[](size_t n,size_t sz)
{if(SetShow)printf("new[](%d,%d): ",(int)n,(int)sz); return malloc(n);}
//---
void *operator new(size_t n,const char*sf,int il)
{if(SetShow)printf("dnew(%d): ",(int)n); return malloc(n,sf,il);}
void *operator new(size_t n,size_t sz,const char*sf,int il)
{if(SetShow)printf("dnew(%d,%d): ",(int)n,(int)sz); return malloc(n,sf,il);}
void *operator new[](size_t n,const char*sf,int il)
{if(SetShow)printf("dnew[](%d) %s: ",(int)n,sf); return malloc(n,sf,il);}
void *operator new[](size_t n,size_t sz,const char*sf,int il)
{if(SetShow)printf("dnew[](%d,%d): ",(int)n,(int)sz); return malloc(n,sf,il);}
//---
void operator delete(void *p)
{if(SetShow)printf("delete: "); free(p);}
void operator delete(void *p,size_t sz)
{if(SetShow)printf("delete(%d): ",(int)sz); free(p);}
void operator delete[](void *p)
{if(SetShow)printf("delete[]: "); free(p);}
void operator delete[](void *p,size_t sz)
{if(SetShow)printf("delete[](%d,%d): ",(int)sz,(int)sz); free(p);}
//---
//#define new new(__FILE__,__LINE__)
//---
//char used128[NMAX/128]={0};
//char used512[NMAX/512]={0};
//char used8192[NMAX/8192]={0};
//char used131072[NMAX/131072]={0};
//char used2097152[NMAX/2097152]={0};

int CheckNewDelete()
{int Set=0;
#ifdef SHOW_MEM_ALLOCATIONS
 for(int i=2;i<NMAX/128;i++)if(used128[i]){printf("memory leak:<%s>#%d: %d\n",sf128[i],il128[i],np128[i]);Set=1;}
 for(int i=0;i<NMAX/512;i++)if(used512[i]){printf("memory leak:<%s>#%d: %d\n",sf512[i],il512[i],np512[i]);Set=1;}
 for(int i=0;i<NMAX/8192;i++)if(used8192[i]){printf("memory leak:<%s>#%d: %d\n",sf8192[i],il8192[i],np8192[i]);Set=1;}
 for(int i=1;i<NMAX/131072;i++)if(used131072[i]){printf("memory leak:<%s>#%d: %d\n",sf131072[i],il131072[i],np131072[i]);Set=1;}
 for(int i=0;i<NMAX/2097152;i++)if(used2097152[i]){printf("memory leak:<%s>#%d: %d\n",sf2097152[i],il2097152[i],np2097152[i]);Set=1;}
#else
 for(int i=2;i<NMAX/128;i++)if(used128[i]){printf("memory leak: %d\n",np128[i]);Set=1;}
 for(int i=0;i<NMAX/512;i++)if(used512[i]){printf("memory leak: %d\n",np512[i]);Set=1;}
 for(int i=0;i<NMAX/8192;i++)if(used8192[i]){printf("memory leak: %d\n",np8192[i]);Set=1;}
 for(int i=1;i<NMAX/131072;i++)if(used131072[i]){printf("memory leak: %d\n",np131072[i]);Set=1;}
 for(int i=0;i<NMAX/2097152;i++)if(used2097152[i]){printf("memory leak: %d\n",np2097152[i]);Set=1;}
#endif
 if(!Set)printf("no memory leaks");
return Set;
}
struct SCheckNewDelete
{
 ~SCheckNewDelete()
 {CheckNewDelete();}
};//VCheckNewDelete;


#ifdef __GNUC__
void CheckNewDeleteC(void)
{int Set=0,i;
#ifdef SHOW_MEM_ALLOCATIONS
 for(i=2;i<NMAX/128;i++)if(used128[i]){printf("gnu memory leak:<%s>#%d: %d\n",sf128[i],il128[i],np128[i]);Set=1;}
 for(i=0;i<NMAX/512;i++)if(used512[i]){printf("gnu memory leak:<%s>#%d: %d\n",sf512[i],il512[i],np512[i]);Set=1;}
 for(i=0;i<NMAX/8192;i++)if(used8192[i]){printf("gnu memory leak:<%s>#%d: %d\n",sf8192[i],il8192[i],np8192[i]);Set=1;}
 for(i=1;i<NMAX/131072;i++)if(used131072[i]){printf("gnu memory leak:<%s>#%d: %d\n",sf131072[i],il131072[i],np131072[i]);Set=1;}
 for(i=0;i<NMAX/2097152;i++)if(used2097152[i]){printf("gnu memory leak:<%s>#%d: %d\n",sf2097152[i],il2097152[i],np2097152[i]);Set=1;}
#else
 for(i=2;i<NMAX/128;i++)if(used128[i]){printf("gnu memory leak: %d\n",np128[i]);Set=1;}
 for(i=0;i<NMAX/512;i++)if(used512[i]){printf("gnu memory leak: %d\n",np512[i]);Set=1;}
 for(i=0;i<NMAX/8192;i++)if(used8192[i]){printf("gnu memory leak: %d\n",np8192[i]);Set=1;}
 for(i=1;i<NMAX/131072;i++)if(used131072[i]){printf("gnu memory leak: %d\n",np131072[i]);Set=1;}
 for(i=0;i<NMAX/2097152;i++)if(used2097152[i]){printf("gnu memory leak: %d\n",np2097152[i]);Set=1;}
#endif
 if(!Set)printf("no memory leaks");
return ;
}
#else
void CheckNewDeleteC(void)
{int Set=0,i;
#ifdef SHOW_MEM_ALLOCATIONS
 for(i=0;i<NMAX/128;i++)if(used128[i]){printf("memory leak:<%s>#%d: %d\n",sf128[i],il128[i],np128[i]);Set=1;}
 for(i=0;i<NMAX/512;i++)if(used512[i]){printf("memory leak:<%s>#%d: %d\n",sf512[i],il512[i],np512[i]);Set=1;}
 for(i=0;i<NMAX/8192;i++)if(used8192[i]){printf("memory leak:<%s>#%d: %d\n",sf8192[i],il8192[i],np8192[i]);Set=1;}
 for(i=0;i<NMAX/131072;i++)if(used131072[i]){printf("memory leak:<%s>#%d: %d\n",sf131072[i],il131072[i],np131072[i]);Set=1;}
 for(i=0;i<NMAX/2097152;i++)if(used2097152[i]){printf("memory leak:<%s>#%d: %d\n",sf2097152[i],il2097152[i],np2097152[i]);Set=1;}
#else
 for(i=0;i<NMAX/128;i++)if(used128[i]){printf("memory leak: %d\n",np128[i]);Set=1;}
 for(i=0;i<NMAX/512;i++)if(used512[i]){printf("memory leak: %d\n",np512[i]);Set=1;}
 for(i=0;i<NMAX/8192;i++)if(used8192[i]){printf("memory leak: %d\n",np8192[i]);Set=1;}
 for(i=0;i<NMAX/131072;i++)if(used131072[i]){printf("memory leak: %d\n",np131072[i]);Set=1;}
 for(i=0;i<NMAX/2097152;i++)if(used2097152[i]){printf("memory leak: %d\n",np2097152[i]);Set=1;}
#endif
 if(!Set)printf("no memory leaks");
return ;
}
#endif
