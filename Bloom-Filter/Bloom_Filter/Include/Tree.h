#ifndef TREE
#define	TREE
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include "List.h"
#include "Bloom_Filter.h"
using namespace std;

///////////////////
//  TREE  CLASS  //
///////////////////
class Tree
{
    private:
        List lista;                // A list when tree is full
        Bloom filter;              //A bloom filter
        int total_depth;           //Total depth of tree
        int total_kids;            //Total nodes in tree
        int curr_depth;            //Current depth ,when inserting nodes
        bool full_tree;            //Check if tree is full
        bool empty_list;           //check if list id empty,end of game
        bool full_search;          //check for a message if tree is full
        struct node{               //Node of the tree
            int number_of_kids;    //numbers of kids
            bool check;            //Check for if the node has been used
            const char * data_word;//data
            node *right_sibling;   //pointer to sibling
            node *father;          //pointer to father
            node **kids;           //array of kids
        };
        struct list_node{          //List for the printing and deleting the tree
            node *fath;
            node *data;
            list_node *next;
        };
        node* root;                //points root
        node* temp;                //pointers
        node* curr_node;
        node* printer;
        list_node* head_list;
        list_node* curr_list;
    public:
        Tree();                             //constructor
        node* createnode(const char *);     //create node
        void set_tree_depth(int);           //set max depth
        void initialize_tree(int,int);      //initialize tree
        void allocate_node_array(node* );   //allocate array kids to node
        void set_tree();                    //set tree
        void print_tree();                  //print tree
        void delete_tree();                 //delete the tree
        void set_bloom_size(int,int);       //set size to bloom
        const char * insert_words_Tree(int,const char **);//insert words
        const char * next_word_to_test();   //send next word to main
        bool check_tree_depth();            //checks if tree is full
        bool end_of_game();                 //check if there are no more words to check
        int Tree_total_words();             //for the statistics
        int total_kids_in_list();
        float full_percentage_filter_tree();

        void insert_node_to_helper_list(node *);//for the list,print delete
        void delete_nodes();
};

#endif
