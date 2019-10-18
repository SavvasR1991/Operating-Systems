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
    bytes_size=k;           //total bytes
    char zero=0x00;         //allocate memory
    bloom_array=(char *)malloc(bytes_size*sizeof(char));
    for(i=0;i<bytes_size;i++)//initialize array to zeros
    {                           //ex:M=8->00000000
        bloom_array[i]=bloom_array[i]&zero;
    }
    num_hash=l;             //set number of hash functions
}

/////////////////////////////////////
//    CHECK IF WOED IS IB BLOOM    //
/////////////////////////////////////
bool Bloom::check_word(const char *word)
{
    unsigned long long int result_hash;
    int i;
    int j;
    int check=0;
    char test;
    char compare_word;
    int curr;
    int byte_part;
    int bit_part;
    for(i=0;i<num_hash;i++)
    {   test=0x01;              //mask ex M=8:00000001
        result_hash = hash_by(i,word);//result from hash
        curr=result_hash%(bytes_size*CHAR_BIT);//find position
        byte_part=curr/CHAR_BIT;                //find number of byte
        bit_part=CHAR_BIT-(curr%CHAR_BIT);      //find number of bit
        test=test<<(bit_part-1);                //escalate to the position
        compare_word=bloom_array[byte_part];    //previus case of byte
        bloom_array[byte_part]= bloom_array[byte_part]|test;//new case of byte
        if(compare_word!=bloom_array[byte_part])    //if has change
        {                                   //count how many times(each hash)
            check++;
            bits_used++;                    //+ used bits
        }
    }
    if(check>0)                         //at least one change
    {
        return true;                //insert word
    }
    else
    {
        return false;               //don't insert
    }
}

/////////////////////////////////////
//     CHECK IF BLOOM IS FULL      //
/////////////////////////////////////
bool Bloom::check_bloom_full()
{
    char test2=0xFF; //ex M=8:11111111
    int check = 0;
    int i;
    for(i=0;i<bytes_size;i++)//check each byte
    {                   //if byte = 11111111
        if(bloom_array[i]==test2)//full byte
        {
            check++;
        }
    }
    if(check>=bytes_size)   //if all bytes are full
    {
        cout<<">>Bloom filter is full..."<<endl;
        return true;
    }
    else
    {
        return false;
    }
}

/////////////////////////////////////
//    RETURN USED_BITS/TOTAL_BITS  //
/////////////////////////////////////
float Bloom::full_percentage_bloom()
{
    return ((float)(100*bits_used))/((float)(bytes_size*CHAR_BIT));
    // (100*bits_used)/(bytes_size*CHAR_BIT)
}


