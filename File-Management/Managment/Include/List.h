#ifndef LIST
#define	LIST

#include "Libraries.h"


///////////////////
//  LIST  CLASS  //
///////////////////
class List
{
    private:
        typedef struct node_list            //List node
        {
            int worker_id;        	    //Data
            char *named_pipe_worker;    //Data
            node_list* next;                //pointer to next
        }*nodePtr;
        nodePtr head;                       //Begin
        nodePtr curr;                       //end
        nodePtr temp;                       //temp
    public:
        List();                              //constructor
        void insert_worker_list(int,char *);  	     //insert suspended worker to list
        void insert_available_worker_list(int);
        void kill_worker_processes();                //kill processes and free pipes
        void delete_list();                  //delete list
        int return_next_worker_list();       //return next worker available
};


#endif
