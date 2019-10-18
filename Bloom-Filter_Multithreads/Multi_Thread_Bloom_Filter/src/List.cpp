#include "List.h"

///////////////////
//  CONSTRUCTOR  //
///////////////////
List::List() //initialize variables
{
    head=NULL;
    curr=NULL;
    temp=NULL;
    kids=0;
}

////////////////////////////
//  INSERT WORDS TO LIST  //
////////////////////////////
void List::insert_words_list(const char *word)//insert words to list
{
        end_game=false;                     //check if list is empty,no more words
        nodePtr n = new node_list;          //allocate memory
        n->next = NULL;                     //insert data to node
        n->data_word=word;
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
        kids++;                             //+ total nodes in list
      //  }
}

////////////////////////////
//  PRINTS DATA OF LIST   //
////////////////////////////
void List::printer()            //print list
{
    temp=head;
    if(head==NULL)              //if list empty
    {
        cout<<">>List is empty..."<<endl;
    }
    else
    {
        cout<<">>Printing list...."<<endl<<">>Head::=>[";
        while(temp!=NULL)       //print data nodes
        {
            cout<<temp->data_word<<"]-->[";
            temp=temp->next;
        }
        cout<<"]           ..["<<kids<<"]\n";
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

///////////////////////////////
//  CHECKS IF LIST IS EMPTY  //
///////////////////////////////
bool List::check_empty_list()//check if list is empty,to finish search
{
    if(head==NULL)          //is empty
    {
        return true;
    }
    else                    //not empty
    {
        return false;
    }
}

////////////////////////////
//  RETURN WORDS TO TREE  //
////////////////////////////
const char * List::return_next_word_list()//return first word to tree
{
    const char * word;
    if(head!=NULL)              //if list not empty
    {
        kids--;                 //- total number of nodes
        temp=head;
        if(head->next!=NULL)    //if many nodes
        {
            head=head->next;    //point next node
            word=temp->data_word;//return data
            delete temp;        //delete node
            return word;
        }
        else
        {                       //only one node
            word=temp->data_word;
            head=NULL;
            delete temp;        //empty list
            return word;        //return data
        }
    }
}

////////////////////////////
//  RETURN WORDS TO TREE  //
////////////////////////////
int List::return_list_kid()
{       //return list kids
    return kids;
}

