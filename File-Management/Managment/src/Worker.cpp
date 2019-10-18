#include "Worker.h"

void Worker::Worker_Operation()
{
    ifstream inFile;                        //files variables
    ofstream ofFile;
    WorkerList wor_li;                      //list to save the domains
    char path[MSGSIZE];                     //the path from the manager
    char path_buf[]="/tmp/";                //the word for access the named pipe
    char ch;
    char temp;
    char buffer[200];
    char domain[50];
    char buf[10];
    int length_path=strlen(path_buf)+1;     //length of path
    int i;
    int j;
    int k,m=0;
    int num_point;
    int count_point;
    int read_result;                        //variable for read output
    int fd;
    bool check_valid_url;                   //flag for valid url
    bool at_least_one_valid;
    sprintf(buf, "%d", getpid());           //make id process a string
    for(j=0;j<strlen(buf);j++)              //fix the name pipe,/tmp/23345
    {
        path_buf[length_path+j-1]=buf[j];
    }
    path_buf[length_path+j-1]='\0';         //for string
    fd = open(path_buf, O_RDONLY);
    while(1)                                //repeat for ever
    {
        read_result =read (fd,path ,MSGSIZE);//read from pipe
        path[read_result]='\0';
        inFile.open(path);                  //open file
        if(inFile.fail()){                  //check for error
            cout<<">>Error in worker ["<<getpid()<<"],cannot open \""<<path<<"\" inFile.."<<endl;

        }
        else
        {
            cout<<">>File is ready for processing, Worker["<<getpid()<<"] : \""<<path<<"\""<<endl;
            at_least_one_valid=false;
            while(inFile >> noskipws >> ch)     //read all file
            {
                check_valid_url=false;          //flag for valid url from file
                if(ch=='h')                     //first letter h
                {
                    inFile >> noskipws >> ch;   //next
                    if(ch=='t')                 //second letter t
                    {
                        inFile >> noskipws >> ch;//next
                        if(ch=='t')             //third letter t
                        {
                            inFile >> noskipws >> ch;//next
                            if(ch=='p')         //fourth letter p
                            {
                                inFile >> noskipws >> ch;//next
                                if(ch==':')     //fifth letter :
                                {
                                    inFile >> noskipws >> ch;//next
                                    if(ch=='/') //sixth letter /
                                    {
                                        inFile >> noskipws >> ch;//next
                                        if(ch=='/')//seventh letter /
                                        {
                                            i=0;    //initialize variables
                                            j=0;
                                            k=0;
                                            num_point=0;
                                            count_point=0;
                                            inFile >> noskipws >> ch;//next
                                            if(ch=='.') //if first . wrong ,continue to next word
                                            {
                                                continue;
                                            }
                                            while(ch!=' '&&ch!='/'&&ch!='\n') //while space,/,or next line
                                            {
                                                buffer[i]=ch;   //store to buffer
                                                i++;
                                                if((ch>=48&&ch<=57)||(ch>=65&&ch<=90)||(ch>=97&&ch<=122)||ch==46)
                                                {                       //for letters and number only
                                                    if(ch=='.')         //at least one .
                                                    {
                                                        check_valid_url=true;
                                                    }
                                                }
                                                else            //invalid url
                                                {
                                                    check_valid_url=false;
                                                    break;
                                                }
                                                if(ch=='.')         //count the points
                                                {
                                                    num_point++;
                                                }
                                                else
                                                {
                                                    num_point=0;
                                                }
                                                if(num_point>1)//if two or more points in the same time
                                                {
                                                    check_valid_url=false;  //invalid
                                                    break;
                                                }
                                                inFile >> noskipws >> ch;//next
                                            }
                                            buffer[i]='\0';
                                            if(buffer[i-1]=='.') //if point at the end, http://sabbas.gr.
                                            {
                                                check_valid_url=false;
                                            }
                                            j=i;
                                            if(check_valid_url==true) //after valid control,if valid
                                            {
                                                i--;
                                                while(i>=0)         //find the last point,for domains
                                                {
                                                    if(buffer[i]=='.')
                                                    {
                                                        num_point++;
                                                    }
                                                    if(num_point>1)
                                                    {
                                                        i++;
                                                        break;
                                                    }
                                                    i--;
                                                }
                                                if(i<0)
                                                {
                                                    i=0;
                                                }
                                                for(i=i;i<j;i++)    //create domain
                                                {
                                                    domain[k]=buffer[i];
                                                    k++;
                                                }
                                                domain[k]='\0';     //domain ready
                                                wor_li.insert_domains(domain);//insert to list
                                                at_least_one_valid=true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(at_least_one_valid==true)
            {	
                wor_li.create_worker_fileout(path);//create the file out
            }
        }
        inFile.close();                    //close file
        raise(SIGSTOP);                    //send signal to itself
    }
}
