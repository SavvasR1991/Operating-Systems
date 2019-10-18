#ifndef BLOOM_FILTER
#define	BLOOM_FILTER

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "hash.h"
using namespace std;

///////////////////
//  BLOOM CLASS  //
///////////////////
class Bloom
{
    private:
        int bytes_size;                     //total size in bytes
        int num_hash;                       //total number of hash
        float bits_used;                    //total bits used
        char *bloom_array;                  //bloom array
        bool full;                          //check if bloom full
    public:
        Bloom();                               //constructor
        void delete_bloom();                   //delete bloom
        void bloom_filter_allocation(int,int); //allocate byte matrix
        bool check_word(const char *);         //check if word is in bloom
        bool check_bloom_full();               //check if bloom is full
        float full_percentage_bloom();         //used_bits/total_size (%)

};

#endif
