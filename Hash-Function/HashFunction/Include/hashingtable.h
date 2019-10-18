#include<iostream>
#include<string>

using namespace std;

#ifndef HASHINGTABLE_H
#define HASHINGTABLE_H
//////////////////////////////////////////
////        Hashtable struct          ////
//////////////////////////////////////////
class hashtable{

    private:

            /////////////////////////////
            //      Eggrafes           //
            /////////////////////////////
            struct record{                  //H domh giq tis eggrafes
                char* number;
                char  *name;
                char* lastname;
                char* town;
                char* bill;
                record* next;
            };
            /////////////////////////////
            //      Eurethrio          //
            /////////////////////////////
            typedef struct index_list_towns{    //H domh apo ton kathe kombo tou eurethriou pou deixnei se eggrafh
                record *target;
                index_list_towns *next;
            }* nodeptr_towns;
            typedef struct index_list{       //H domh giq to eurethrio
                char *town;                  //Periexei onoma tis polhs
                int total;                   //Periexei to sunoliko arithmo ton sundromitwn tou kathe kombou
                index_list *next;
                nodeptr_towns node_towns;    //Deikths se nodeptr_towns
            }* nodeptr;
            nodeptr head;              //Deikths pou deixnei sthn kefali tou eurethriou
            nodeptr temp;              //Prosorinos deikths sto eurethrio
            nodeptr curr;              //Trexon deikths sto eurethrio
            /////////////////////////////
            // Pinakas katakermatismou //
            /////////////////////////////
            int dimension;              //Diastash tou pinaka katakermatismou
            record** matrix;

    public:
            /////////////////////////////
            //Sunarthseis arxikopoihshs//
            /////////////////////////////
            void setmatrixdim(int dimension);
            void sethashmatrix();
            void inverted_index_setting(char *town,record *p);

            /////////////////////////////
            // Bohthitikes sunarthseis //
            /////////////////////////////
            int hashing(char* var);
            int bucketcounter(int index);
            void deletetownpointer(record *d);
            /////////////////////////////
            //  Zhtoumenes sunarthseis //
            /////////////////////////////
            void insertrecord(char* number,char *name,char * lastname,char * town,char * bill);
            void deleterecord(char* number);
            void query(char *number);
            void population(char *town);
            void top(int k);
            void sum(char *town);
            void findtown(char *town,int l);
            void findtopspender();
            void min_max();
            void exit();

            void printtable();
            void pr();
};



#endif // HASHINGTABLE_H
