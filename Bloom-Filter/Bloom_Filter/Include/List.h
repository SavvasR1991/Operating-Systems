#ifndef LIST
#define	LIST

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
using namespace std;

///////////////////
//  LIST  CLASS  //
///////////////////
class List
{
    private:
        typedef struct node_list            //List node
        {
            const char * data_word;         //Data
            node_list* next;                //pointer to next
        }*nodePtr;
        nodePtr head;                       //Begin
        nodePtr curr;                       //end
        nodePtr temp;                       //temp
        int kids;                           //total nodes
        bool end_game;                      //check if list ends

    public:
        List();                              //constructor
        void insert_words_list(const char *);//insert words to list
        void printer();                      //print list
        void delete_list();                  //delete list
        bool check_empty_list();             //check if list is empty
        const char * return_next_word_list();//return next word to check
        int return_list_kid();               //return list kids
};


#endif
