#ifndef WORKERLIST
#define	WORKERLIST

#include "Libraries.h"



///////////////////
//  WORKERLIST  CLASS  //
///////////////////
class WorkerList
{
    private:
        typedef struct node_list            //List node
        {
            int num_doma;        	        //Data
            string name;
            node_list* next;                //pointer to next
        }*nodePtr;
        nodePtr head;                       //Begin
        nodePtr curr;                       //end
        nodePtr temp;                       //temp
    public:
        WorkerList();                              //constructor
        void insert_domains(string);               //insert domain
        void create_worker_fileout(const char*);   //create file out
        char* file_name(const char *);             //fix file name
        void clear_worker_list();                  //delete
};
#endif
