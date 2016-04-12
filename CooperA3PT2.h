/* Author: Andrew Cooper
* This program consists of three files: CooperA3PT2.c, CooperA3FuncPT2.c, and CooperA3PT2.h.
* Its purpose was to demonstrate the use of semaphors with six child processes accessing shared memory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define SEMPERM  0600
#define TRUE	 	1
#define FALSE    	0

typedef union _semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
} semun;

//	Create and initialize a semaphore with a value of 1
int initsem(key_t semkey);

//Semaphore wait() procedure
int waitsem(int semid);

//Semaphore signal() procedure
int signalsem(int semid);

void semrem(int semid);
