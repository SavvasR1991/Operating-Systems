#include "Bloom_Filter.h"

///////////////////
//  CONSTRUCTOR  //
///////////////////
Bloom::Bloom()//initialize variables
{
    full=false;
    bits_used=0;
}

///////////////////
//  DELETE BLOOM //
///////////////////
void Bloom::delete_bloom()
{
    free(bloom_array);//free memory
    cout<<">>Bloom filter deleted..."<<endl;
}

/////////////////////////////////
//  ALLOCATE MEMORY FOR ARRAY  //
/////////////////////////////////
void Bloom::bloom_filter_allocation(int k,int l)
{
    int i;
    int j=0;
    int temp = BLOOM_FILTER_DIVISION-1;
    bytes_size=k;           //total bytes
    char zero=0x00;         //allocate memory
    bloom_array=(char *)calloc(bytes_size,sizeof(char));
    if(bloom_array==NULL)
    {
        cout<<">>Error,Cannot allocate memory for bloom filter..."<<endl;
        exit(EXIT_FAILURE);
    }
    for(i=0;i<bytes_size;i++)//initialize array to zeros
    {
        bloom_array[i]=bloom_array[i]&zero;
    }
    num_hash=l;             //set number of hash functions
}

