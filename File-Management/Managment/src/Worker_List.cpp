#include "Worker_List.h"

std::string GetCurrentWorkingDir( void ) {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}

///////////////////
//  CONSTRUCTOR  //
///////////////////
WorkerList::WorkerList() //initialize variables
{
    head=NULL;
    curr=NULL;
    temp=NULL;
}

//////////////////////
//  insert_domains  //
//////////////////////
void WorkerList::insert_domains(string domain)
{
    if(head==NULL)                        //first node
    {
        nodePtr n = new node_list;        //allocate memory
        n->next = NULL;                   //insert data to node
        n->num_doma=1;                    //initialize domain
        n->name=domain;                   //set domain name
        head = n;                         //set head
        curr=head;                        //set current
    }
    else                                  //no first node
    {
        curr=head;                        //set current
        while(curr->next!=NULL)           //find the last node
        {
            if(domain==curr->name)        //if the domain already exist
            {
                curr->num_doma++;         //plus one
                break;
            }
            curr = curr->next;
        }
        if(curr->next==NULL)              //if we searched all the list
        {
            if(domain==curr->name)        //check last node
            {
                curr->num_doma++;         //plus one
            }
            else                          //create new node
            {
                nodePtr n = new node_list;//allocate memory
                n->next = NULL;           //insert data to node
                n->num_doma=1;
                n->name=domain;
                curr->next = n;
                curr=n;
            }
        }
    }
}

///////////////////////////////
//   create_worker_fileout   //
///////////////////////////////
void WorkerList::create_worker_fileout(const char* path)
{
   curr=head;
   ofstream ofFile;
   char *name;
   int index;

   if(head!=NULL)                   //if the is a list
   {
       name=file_name(path);        //fix the name
       std::string path2(GetCurrentWorkingDir());
       index = path2.find("build", index);
       path2.replace(index, 5+strlen(name), name);

       ofFile.open(path2.c_str());//create-open file
       if(ofFile.fail()){           //check for error
            cout<<">>Error in worker ["<<getpid()<<"],cannot open "<<name<<" outFile.."<<endl;
            delete name;
            exit(EXIT_FAILURE);     //exit error
       }
       while(curr->next!=NULL)      //find the last node
       {
            ofFile<<curr->name;     //write to file the results
            ofFile<<" ";
            ofFile<<curr->num_doma;
            ofFile<<"\n";
            curr = curr->next;      //next node

       }
       ofFile<<curr->name;          //write the last node
       ofFile<<" ";
       ofFile<<curr->num_doma;
       ofFile<<"\n";
       ofFile.close();              //close file
       delete name;

   }
   clear_worker_list();             //delete list
}

///////////////////
//   file_name   //
///////////////////
char* WorkerList::file_name(const char *path)
{
    char str[1000];
    char p[]="Workers_Results/";        //string for the destination of the files
    strncpy(str, path, sizeof(str));    //fix the final path of destination
    char* parts[100] = {0};             //variables to take the name of file
    unsigned int index = 0;
    parts[index] = strtok(str,"/");
    while(parts[index] != 0)            //find the name for name.out
    {
        ++index;
        parts[index] = strtok(0, "/");
    }
    strcat(p,parts[index-1]);           //take the name
    strcat(p,".out");                   //put the final name.<out>
    char* str2 = new char[strlen(p) + 1];
    strcat(str2,p);

    return str2;                           //return
}

/////////////////////////
//  clear_worker_list  //
/////////////////////////
void WorkerList::clear_worker_list()
{
    curr=head;              //set current
    while(curr->next!=NULL) //search all list
    {
        temp=curr->next;    //set temp
        delete curr;        //delete bode
        curr=temp;
    }
    delete curr;            //delete last node
    head = NULL;            //reset head
}







