#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <time.h>
#include "oracle.h"
#include "Tree.h"
using namespace std;

int main(int argc, char *argv[])
{
////////////////////////////////////
//----------VARIABLES-------------//
////////////////////////////////////
    Tree word_tree;
    bool arg_check=false;
    bool check_game = true;
    int num_hash_fun;
    int tree_depth;
    int size_bloom;
    int i;
    int total_seeds=0;
    const char **word_array=NULL;
    const char* pointer;
    clock_t tStart = clock();
    initSeed(152);
//////////////////////////////////////////////////////////////////////////////////////////////
//--------------------CHECK ARGUMENTS AND INPUT FROM USER-----------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////
    if ( argc != 5 )   //check if user insert correct number of arguments (4)
    {
        cout<<">>Wrong input from commant list, must insert 4 arguments :"<< endl;
        cout<<">>--->[ ./invoke-oracle -k NUM SIZE DEPTH] or [./invoke-oracle SIZE DEPTH";
        cout<<" -k NUM ]\n>>Program terminated...."<<endl;
        return 0;
    }
    if(strcmp(argv[1],"-k")==0)             //check case [./invoke-oracle -k NUM SIZE DEPTH]
    {
        num_hash_fun=atoi(argv[2]);
        size_bloom=atoi(argv[3]);
        tree_depth=atoi(argv[4]);
        arg_check=true;                     // case [./invoke-oracle -k NUM SIZE DEPTH] is correct
    }
    else                                    //check case [./invoke-oracle SIZE DEPTH -k NUM]
    {
        size_bloom=atoi(argv[1]);
        tree_depth=atoi(argv[2]);
        if(strcmp(argv[3],"-k")==0)
        {
            num_hash_fun=atoi(argv[4]);
            arg_check=true;                 // case [./invoke-oracle SIZE DEPTH -k NUM] is correct
        }
    }
    if(arg_check==false)                    //wrong input from user
    {
        cout<<">>Wrong input,must be like this:"<<endl;
        cout<<">>--->[ ./invoke-oracle -k NUM SIZE DEPTH] or [./invoke-oracle SIZE DEPTH";
        cout<<" -k NUM ]\n>>Program terminated...."<<endl;
        exit(1);
    }
    if(num_hash_fun<=0)                     //case user put negative or zero number of hash functions
    {
        num_hash_fun=1;                     //set 1
    }
    if(size_bloom<=0)                       //case user put negative or zero size of bloom filter
    {
        size_bloom=1;                       //set 1
    }
//////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------MAIN PROGRAM ,FIND SECTER WORD-------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    word_tree.set_tree_depth(tree_depth);                        //set tree depth
    word_tree.initialize_tree(size_bloom,num_hash_fun);          //initialize tree,create root,set size filter,#hash
    word_array=oracle(" ");                                      //first input to oracle
    while(word_array!=NULL)                                      //while find secret word
    {
        i=0;
        check_game = word_tree.end_of_game();                    //check if there are no more words to check(list is empty)
        if(check_game==false)                                    //oracle wins
        {
            cout<<">>Program could not find secret word,no more words to check...oracle wins!"<<endl;
            cout<<">>----------[Statistics]----------"<<endl;    //print statistics
            cout<<">>--->Words used                  : "<<total_seeds<<" words"<<endl;
            cout<<">>--->Depth size of tree          : "<<tree_depth<<" levels"<<endl;
            cout<<">>--->Words saved to tree         : "<<word_tree.Tree_total_words()<<" words"<<endl;
            cout<<">>--->Number of hash functions    : "<<num_hash_fun<<" functions"<<endl;
            cout<<">>--->Size of bloom filter        : "<<size_bloom<<" bytes"<<endl;
            cout<<">>--->Percentage Tree_W/Total_W   : "<<(100*((float)word_tree.Tree_total_words())/((float)total_seeds))<<"%"<<endl;
            cout<<">>--->Percentage Bloom filter used: "<<word_tree.full_percentage_filter_tree()<<"%"<<endl;
            cout<<">>--->Helper word list has        : "<<word_tree.total_kids_in_list()<<" words"<<endl;
            cout<<">>--->Helper word Percentage      : "<<(100*(float)word_tree.total_kids_in_list())/((float)(total_seeds))<<"%"<<endl;
            cout<<">>--->Execution time              : "<<(double)(clock() - tStart)/(CLOCKS_PER_SEC)<<" sec"<<endl;
            cout<<">>--->Words checked per sec       : "<<((float)total_seeds)/((float)((double)(clock() - tStart)/(CLOCKS_PER_SEC)))<<" words/sec"<<endl;
            cout<<">>----------[Statistics]----------"<<endl;    //print statistics
            word_tree.delete_tree();
            cout<<">>End of program..."<<endl;
            exit(1);
        }
        while(word_array[i]!=NULL)                              //count the number of words in the matrix
        {
            i++;
        }
        total_seeds++;
        pointer=word_tree.insert_words_Tree(i,word_array);      //insert word to tree
        cout<<">>Seed["<<total_seeds<<"]  :"<<pointer<<endl;    //print checked word
        word_array=oracle(pointer);
    }                                                           //user wins
    cout<<">>Secret word founded !!!You win!!!..."<<endl;
    cout<<">>Secret word :!!!!"<<pointer<<"!!!!"<<endl;
    cout<<">>----------[Statistics]----------"<<endl;           //print statistics
    cout<<">>--->Words used                  : "<<total_seeds<<" words"<<endl;
    cout<<">>--->Depth size of tree          : "<<tree_depth<<" levels"<<endl;
    cout<<">>--->Words saved to tree         : "<<word_tree.Tree_total_words()<<" words"<<endl;
    cout<<">>--->Number of hash functions    : "<<num_hash_fun<<" functions"<<endl;
    cout<<">>--->Size of bloom filter        : "<<size_bloom<<" bytes"<<endl;
    cout<<">>--->Percentage Tree_W/Total_W   : "<<(100*((float)word_tree.Tree_total_words())/((float)total_seeds))<<"%"<<endl;
    cout<<">>--->Percentage Bloom filter used: "<<word_tree.full_percentage_filter_tree()<<"%"<<endl;
    cout<<">>--->Helper word list has        : "<<word_tree.total_kids_in_list()<<" words"<<endl;
    cout<<">>--->Helper word Percentage      : "<<(100*(float)word_tree.total_kids_in_list())/((float)(total_seeds))<<"%"<<endl;
    cout<<">>--->Execution time              : "<<(double)(clock() - tStart)/(CLOCKS_PER_SEC)<<" sec"<<endl;
    cout<<">>--->Words checked per sec       : "<<((float)total_seeds)/((float)((double)(clock() - tStart)/(CLOCKS_PER_SEC)))<<" words/sec"<<endl;
    cout<<">>----------[Statistics]----------"<<endl;    //print statistics
    word_tree.delete_tree();                                    //delete tree,list,bloom filter
    cout<<">>End of program..."<<endl;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return 0;
}

