#include "Libraries.h"
#include "List.h"
#include "Listener.h"
#include "Worker.h"

pid_t listener_pid;
pid_t worker_pid=10;
pid_t pid;
int num_files=0;
int num_of_forks=0;
int status=0;
int num_worker_reused=0;
List workers_id_list;
List available_workers_list;


void SIGINT_handler(int signal)     //catch Ctrl^C
{
    if(worker_pid!=0)                               //only for manager
    {
        cout<<"\n>>Manager["<<getpid()<<"] received signal :"<<signal<<" (Ctrl^C,SIGINT) from user.."<<endl;//ektupwsh tou lambanimenou shmaros
        cout<<">>Killing all processes,workers and listener.."<<endl;
        cout<<">>Closing all named pipes.."<<endl;
        fflush(NULL);
        kill(listener_pid, SIGKILL);                //kill listener
        workers_id_list.kill_worker_processes();    //kill workers
        workers_id_list.delete_list();              //delete list
        available_workers_list.delete_list();       //delete list
        cout<<">>Program terminated successfully..!!"<<endl;
        cout<<">>----------[Statistics]----------"<<endl;    //print statistics
        cout<<">>--->Files used                  : "<<num_files<<" Files"<<endl;
        cout<<">>--->Worker created              : "<<num_of_forks<<" Workers"<<endl;
        cout<<">>--->Workers reused              : "<<num_worker_reused<<" Workers"<<endl;
        cout<<">>--->Listener created            : 1 Listeners"<<endl;
        cout<<">>----------[Statistics]----------"<<endl;    //print statistics
	cout<<"End of programm..."<<endl;        
	exit(EXIT_SUCCESS);
    }
}

void SIGCHLD_handler(int signal)
{
    if(worker_pid!=0)
    {
        pid_t waita;
        int status;
        if((waita=waitpid(-1,&status,WUNTRACED|WNOHANG))>0)
        {
            if (WIFSTOPPED(status)) {
                available_workers_list.insert_available_worker_list(waita);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if ( argc != 3 )   //check if user insert correct number of arguments (2)
    {
        cout<<">>Wrong input from command line, must insert 2 arguments :"<< endl;
        cout<<">>--->[./sniffer -k [directory path]";
        cout<<"\n>>Program terminated...."<<endl;
        exit(EXIT_FAILURE);
    }
     if(strcmp(argv[1],"-k")!=0)                    //wrong input from user
    {
        cout<<">>Wrong input,no path flag,must be like this:"<<endl;
        cout<<">>--->[./sniffer -k [directory path]";
        cout<<"\n>>Program terminated...."<<endl;
        exit(EXIT_FAILURE);
    }

    //set variables
    static struct sigaction act;        //signal handler for ctrl^C
    static struct sigaction act2;        //signal handler for ctrl^C
    char inbuf [MSGSIZE];
    char path_buf[]="/tmp/";            //string for named pipes
    char buf[20];                       //for id of child
    int p[2];                           //pipe
    int rsize=1;                        //result from read
    int count_rsize;                    //count rsize
    int i;
    int j;
    int path_length=strlen(argv[2]);    //path from user length
    int length_path=strlen(path_buf)+1; //path for named pipes length
    int writefd;                        //write result
    int temp_id;
    bool flag_available_worker;
    sigset_t  mask1;
    Listener listen;                    //for listener
    Worker work;                        //for worker

    if(worker_pid!=0)                   //only for manager
    {
        act.sa_handler =SIGINT_handler;     //mask for SIGINT
        sigfillset (&(act.sa_mask));
        sigaction (SIGINT , &act , NULL);   //catch and process the ctrl^C

        act2.sa_handler =SIGCHLD_handler;     //mask for SIGINT
        sigfillset (&(act2.sa_mask));
        sigaction (SIGCHLD , &act2 , NULL);   //catch and process the ctrl^C
    }
    cout<<">>Insert files to directory :\""<<argv[2]<<"\" for monitoring.."<<endl;
    cout<<">>To end program press : Ctrl ^ C.."<<endl;
    if(pipe(p)==-1)         //open simple pipe for Listener
    {
        cout<<">>Error due piping manager["<<getpid()<<"] with listener...\n>>End of program..."<<endl;
        exit (EXIT_FAILURE);
    }
    cout<<">>Manager id is: ["<<getpid()<<"]\n>>Piping Manager-Listener success!"<<endl;

    listener_pid = fork ();         //Create listener process
    if(listener_pid == -1)
    {
        cout<<">>Error due forking listener...\n>>End of program..."<<endl;
        exit (EXIT_FAILURE);
    }
    if(listener_pid == 0)       //We are at the listener process
    {
        cout<<">>Fork success!Listener id is: ["<<getpid()<<"]"<<endl;
        listen.Listener_Operation(p,argv[2]);
    }
    else                        //We are at the manager process
    {
        dup2 (p[READ],0);       //set the output of pipe for manager
        while(1)          //read from pipe until error in pipe
        {
                rsize =read (p[0],inbuf ,MSGSIZE);  //read from pipe
                if(rsize>0)
                {
                    count_rsize=0;
                    while(count_rsize<rsize)    //read each digit of the output of pipe
                    {
                        i=0;
                        while(inbuf[count_rsize]!='\n') //while reach new line
                        {
                            if(i>path_length)           //ignore the useless messages of inotifywait
                            {
                                inbuf[i]=inbuf[count_rsize+8];  //set the buffer
                            }
                            i++;
                            count_rsize++;
                        }
                        num_files++;        //for the statistics
                        count_rsize++;      //statistics
                        inbuf[i-8]='\0';    //end of the final string path
                        //cout<<"kkkk----> "<<available_workers_list.return_next_worker_list()<<endl;
                        temp_id=available_workers_list.return_next_worker_list();
                        if(temp_id<0)  //if there are no workers available
                        {
                            flag_available_worker = false;  //for the creation of new named pipe
                            worker_pid = fork ();           //create worker
                            if(worker_pid == -1)            //check error due forking
                            {
                                cout<<">>Error due forking worker...\n>>End of program..."<<endl;
                                exit (EXIT_FAILURE);
                            }
                            num_of_forks++;         //statistics
                            if(worker_pid == 0)     //workers operation
                            {
                                work.Worker_Operation();//operation function
                            }
                        }
                        else            //there are workers available
                        {
                            flag_available_worker = true;       //to use again the already existed named pipe
                            worker_pid = temp_id;//take the first available worker
                            kill(worker_pid,SIGCONT);                   //make the worker ready to read
                            num_worker_reused++;
                        }
                        if(worker_pid!=0)       //manager operation
                        {
                            sprintf(buf, "%d", worker_pid);     //make the id of worker a string
                            for(j=0;j<strlen(buf);j++)          //create the name of named pipe
                            {
                                path_buf[length_path+j-1]=buf[j];
                            }
                            path_buf[length_path+j-1]='\0';     //a string,named pipe(ex. "/tmp/2345")
                            if(flag_available_worker==false)    //new worker,create new pipe
                            {
                                if ( (mkfifo(path_buf, PERMS) < 0) && (errno !=   EEXIST) )//create,check error
                                {
                                    cout<<">>Error ,manager can't create FIFO pipe...\n>>End of program..."<<endl;
                                    exit(EXIT_FAILURE);
                                }
                                workers_id_list.insert_worker_list(worker_pid,path_buf);//add worker to total worker list
                            }
                            if ( (writefd = open(path_buf, O_RDWR))  < 0)   //open pipe
                            {
                                cout<<">>Error ,manager can't open FIFO pipe...\n>>End of program..."<<writefd<<endl;
                                exit(EXIT_FAILURE);
                            }
                            if (write(writefd, inbuf, strlen(inbuf)) != strlen(inbuf))//write to pipe
                            {
                                cout<<">>Error ,manager can't write to FIFO pipe...\n>>End of program..."<<endl;
                                exit(EXIT_FAILURE);
                            }
                        }
                   }
                }
        }//if we arrive here there an error due reading
        cout<<">>Error to the manager:["<<getpid()<<"]...\n>>End of program..."<<rsize<<endl;
    }
    
    exit(EXIT_FAILURE);      //terminate
}
