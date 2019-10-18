#ifndef BLOOM_FILTER
#define	BLOOM_FILTER

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "hash.h"
#include "Operations.h"

using namespace std;

///////////////////
//  BLOOM CLASS  //
///////////////////
class Bloom
{
    public:
        int bytes_size;                     //total size in bytes
        int num_hash;                       //total number of hash
        int num_sections;
        float bits_used;                    //total bits used
        char *bloom_array;                  //bloom array
        char *thread_sections_array;
        bool full;
                               //check if bloom full
        Bloom();                               //constructor
        void delete_bloom();                   //delete bloom
        void bloom_filter_allocation(int,int); //allocate byte matrix
};

#endif
