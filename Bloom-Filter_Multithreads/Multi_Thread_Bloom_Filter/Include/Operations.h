#ifndef OPERATIONS
#define	OPERATIONS

/////////////////////////
//      LIBRARIES      //
/////////////////////////


//contains all the required libraries
//and defines
/*------------DEFINES-------------*/
#define MAX_THREADS 50
#define RANDOM_BIG_NUM 1000
#define BLOOM_FILTER_DIVISION 64
#define RANDOM_STRING_LENGTH 20
#define NUM_WAIT_CONNECTION_Q 10

/*------------LIBRATIES----------*/
#include "Bloom_Filter.h"
#include "oracle.h"
#include "List.h"
#include <pthread.h>
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
#include <limits.h>
#include <time.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <ctype.h>
#include <netdb.h>

//struct for the arguments for the find_threads
 typedef struct thread_data
{
    int thread_repeats; //time of repeat
    int num_hashing;    //number of hash function
    int sections;       //number of section of bloom filter
    int thbloom_size;   //size of bloom

}thread_data;

//struct for the arguments for the server_thread
 typedef struct server_thread_data
{
    int port_server_thr;    //port for server
    int num_hashing;        //number of hash
    int thbloom_size;       //bloom size
    int threads;            //number of threads
    int repeats;            //repeat number
    int sections;           //number of section
    int seed;               //initializer of oracle

}server_thread_data;

//struct for the arguments for the server_worker_thread
 typedef struct server_worker_thread_data
{
    int newsocket;      //port for server
    int num_hashing;    //number of hash
    int thbloom_size;   //bloom size
    int threads;        //number of threads
    int repeats;        //repeat number
    int seed;           //initializer of oracle
    int sections;       //number of section
}server_worker_thread_data;

#endif

