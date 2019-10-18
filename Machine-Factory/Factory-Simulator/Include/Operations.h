#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>


#define MAX_CHAR_TYPE 20

#define NUM_OF_PROCESSES 8

#define SHM_PAINTER (key_t) 3889
#define SHM_CONSTRUCTION (key_t) 3890
#define SHM_CONTROL (key_t) 3891

#define SEM_PREPARED_PROCESSES (key_t) 3213
#define SEM_START_PROCESSES (key_t) 3214

#define SEM_PAINTER (key_t) 3215
#define SEM_PAINTER_CONTROL_BUSY (key_t) 3216
#define SEM_CONSTRUCTION (key_t) 3217
#define SEM_CONTROL1 (key_t) 3218
#define SEM_CONTROL2 (key_t) 3219
#define SEM_CONTROL3 (key_t) 3220
#define SEM_PART (key_t) 3221

#define PERMS 0666


union senum
{
    int val;
    struct semid *buf;
    unsigned short *semarray;
};

typedef struct shm_data_1
{
    int ID;
    int piece;
    int type;
    char communication[MAX_CHAR_TYPE];
    int  time;
}shm_data_1;


void down(int);

void up(int);


#endif
