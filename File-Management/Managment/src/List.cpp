#include "List.h"

///////////////////
//  CONSTRUCTOR  //
///////////////////
List::List() //initialize variables
{
    head=NULL;
    curr=NULL;
    temp=NULL;
}

////////////////////////////
//  INSERT WORDS TO LIST  //
////////////////////////////
void List::insert_worker_list(pid_t id,char *path)//insert words to list
{
        nodePtr n = new node_list;          //allocate memory
        n->next = NULL;                     //insert data to node
        n->worker_id=id;
        char *  insert_node_path = ( char *)calloc(1,sizeof(path));
        if(insert_node_path==NULL)
        {
            cout<<">>Error in memory allocation in Manager..."<<endl;
            exit(EXIT_FAILURE);
        }
        strcpy(insert_node_path,path);      //copy the word
        n->named_pipe_worker=insert_node_path;
        if(head!=NULL)                      //if there are  nodes in list
        {
            curr = head;
            while(curr->next!=NULL)         //find the last node
            {
                curr = curr->next;
            }
            curr->next = n;
        }
        else                                //if there are no nodes in list
        {
            head = n;                       //head is the first node
        }
}

void List::insert_available_worker_list(pid_t id)
{
    nodePtr n = new node_list;          //allocate memory
    n->next = NULL;                     //insert data to node
    n->worker_id=id;
    if(head!=NULL)                      //if there are  nodes in list
    {
        curr = head;
        while(curr->next!=NULL)         //find the last node
        {
            curr = curr->next;
        }
        curr->next = n;
    }
    else                                //if there are no nodes in list
    {
        head = n;                       //head is the first node
    }

}

////////////////////////////
//  PRINTS DATA OF LIST   //
////////////////////////////
void List::kill_worker_processes()
{
    temp=head;
    int i=1;
    if(head==NULL)              //if list empty
    {
        cout<<">>No Files inserted..."<<endl;
    }
    else
    {
        while(temp!=NULL)       //print data nodes
        {
            kill(temp->worker_id,SIGKILL);    //kill kids processes
            printf(">>%4d",i);
            cout<<"o Worker:["<<temp->worker_id<<"] ,closing pipe :\""<<temp->named_pipe_worker<<"\""<<endl;
            if ( unlink(temp->named_pipe_worker) < 0) //unlike named pipes
            {
                cout<<">>Error manager :["<<getpid()<<"] can't unlink.."<<endl;
                exit(1);
            }
            temp=temp->next;
            i++;
        }
    }
}

////////////////////////////
//  DELETE NODES OF LIST  //
////////////////////////////
void List::delete_list()        //deletes list
{
    if(head==NULL)              //empty list
    {
        delete head;
    }
    else if(head->next==NULL)   //only one node
    {
        delete head;
    }
    else                        //many nodes
    {
        temp=head;
        curr=head->next;
        while(curr!=NULL)       //delete each node
        {
            delete temp;
            temp=curr;
            curr=curr->next;
        }
        delete temp;
    }
}


////////////////////////////
//  RETURN WORDS TO TREE  //
////////////////////////////
int List::return_next_worker_list()//return first id to tree
{
    pid_t id;
    if(head!=NULL)              //if list not empty
    {
        temp=head;
        if(head->next!=NULL)    //if many nodes
        {
            head=head->next;    //point next node
            id=temp->worker_id;//return data
            delete temp;        //delete node
            return id;
        }
        else
        {                       //only one node
            id=temp->worker_id;
            head=NULL;
            delete temp;        //empty list
            return id;        //return data
        }
    }
    else
    {
        return -1;
    }
}


