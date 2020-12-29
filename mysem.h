#ifndef MYSEM_H
#define MYSEM_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

//#define MAXSEM1 50


extern void myseminit( int val);

extern void mysemp(unsigned short nthsems);

extern void mysemv(unsigned short nthsems);

extern int mysemval(int semNum);

extern int getMAXSEM1();

#endif // MYSEM_H
