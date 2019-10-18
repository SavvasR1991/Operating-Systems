#ifndef OPERATIONSSTATISTICS_H
#define OPERATIONSSTATISTICS_H

#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>

#define SHM_STATISTICS (key_t) 1891

#define PERMS 0666

using namespace std;


typedef struct shm_data_2
{
    int part1[100000];
    int part2[100000];
    int part3[100000];
}shm_data_2;


#endif
