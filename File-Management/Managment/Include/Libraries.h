#ifndef LIBRARIES
#define	LIBRARIES

/////////////////////////
//      LIBRARIES      //
/////////////////////////


#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

//contains all the required libraries
//and defines
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fstream>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <sys/resource.h>
#define READ 0
#define WRITE 1
#define MSGSIZE 1024
#define PERMS   0666

using namespace std;
extern int errno;
#endif

