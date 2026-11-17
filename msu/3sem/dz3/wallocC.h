#pragma once
//define SHOW_MEM_ALLOCATIONS to show allocate/free operations
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;
//---
#define NMAX 300000000
#define LMAX 100000
//extern char p[NMAX][LMAX];
//extern int np[NMAX]; //инициализацция не обязательна
//extern char used[NMAX];
//extern char sf[NMAX][128]; extern int il[NMAX];
extern void *malloc(size_t n);
extern void *malloc(size_t n,const char*sf,int il);
extern void free(void *r);
extern void *operator new(size_t n);
extern void *operator new(size_t n,size_t sz);
extern void *operator new[](size_t n);
extern void *operator new[](size_t n,size_t sz);
//---
extern void *operator new(size_t n,const char*sf,int il);
extern void *operator new(size_t n,size_t sz,const char*sf,int il);
extern void *operator new[](size_t n,const char*sf,int il);
extern void *operator new[](size_t n,size_t sz,const char*sf,int il);
//---
extern void operator delete(void *p);
extern void operator delete(void *p,size_t sz);
extern void operator delete[](void *p);
extern void operator delete[](void *p,size_t sz);
//---
int CheckNewDelete();
#define new new(__FILE__,__LINE__)
