#ifndef PROCESSES_H
#define PROCESSES_H

#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <signal.h>
#include <string.h>
#include <time.h>       
#include "Operations.h"

using namespace std;

void Part(int,int);
void Painter(int);
void Control(int,int);
void Contruction(int);

#endif
