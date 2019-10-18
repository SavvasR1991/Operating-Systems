#include <iostream>
#include "oracle.h"
#include "main_functions.h"
#include "Operations.h"
#include <time.h>
using namespace std;

///////////////////////////////////////////
//----------GLOBAL VARIABLES-------------//
//////////////////////////////////////////////////////
Bloom bloom_filter;                                 //
ofstream file_statistics_output;                    //
int total_word_used=0;                              //
int total_word_wasted=0;                            //
bool founded_word=false;                            //
bool end_of_programm=false;                         //
int perc_bloom=0;                                   //
int serversock;                                     //
int num_connection=0;                               //
//mutexes                                           //
pthread_mutex_t *mutex_array;                       //
pthread_mutex_t mutex_founded_word;                 //
pthread_mutex_t mutex_file_statistics_output;       //
pthread_mutex_t mutex_end_of_program;               //
//thread operation                                  //
void *thread_find_word_operation(void *arg);        //
void *server_thread_operation(void *arg);           //
void *server_worker_thread_operation(void *arg);    //
//////////////////////////////////////////////////////

//////////////////////
//      MAIN        //
//////////////////////
int main(int argc, char *argv[])
{
////////////////////////////////////
//----------VARIABLES-------------//
////////////////////////////////////
    int num_threads,num_restarts,port,num_hash,seed,num_sections,bloom_size, client_sock,client_port,temp_num_threads=RANDOM_BIG_NUM,count_rsize;
    int i,j=0,sl,error_thread,k,mm,check_argum_from_serv,rsize_bloom;
    char *logfile, address[20] ,buf[1000],temp[100];
    bool client_mode=false,end_read=false;;
    double time_spent;
    clock_t beginn, endd;
    pthread_t *total_threads,server_thread;
    struct thread_data *ptr=(thread_data*)malloc(sizeof(thread_data));
    struct server_thread_data *ser_th_ptr=(server_thread_data*)malloc(sizeof(server_thread_data));
    socklen_t clientlen;
    struct sockaddr_in server,client;
    struct sockaddr *serverptr=(struct sockaddr *)&server;
    struct hostent  *rem_client;
//////////////////////////////////////////////////////////////////////////////////////////////
//--------------------CHECK ARGUMENTS AND INPUT FROM USER-----------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////
    if ( argc != 10 )   //check if user insert correct number of arguments (10)
    {
        if(argc==6)
        {
            num_hash=3;
        }
        else if(argc==8)
        {
            if(strcmp(argv[6],"-k")==0)
            {
                num_hash=atoi(argv[7]);
            }
            else if(strcmp(argv[6],"-l")==0)
            {
                num_hash=3;
                client_mode=true;
                strcpy(address,argv[7]);
            }
            else
            {
                print_comm_line_description_message();
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            print_comm_line_description_message();
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if(strcmp(argv[6],"-k")==0)
        {
            num_hash=atoi(argv[7]);
        }
        else
        {
            print_comm_line_description_message();
            exit(EXIT_FAILURE);

        }
        if(strcmp(argv[8],"-l")==0)
        {
            client_mode=true;
            strcpy(address,argv[9]);

        }
        else
        {
            print_comm_line_description_message();
            exit(EXIT_FAILURE);
        }
    }
    cout<<">>Insert seed for oracle function : ";   //insert seed for oracle
    cin>>seed;
////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------INITIALATION OF ARGUMENTS AND INPUT FROM USER-----------------------------------//
////////////////////////////////////////////////////////////////////////////////////////////////////////
    beginn = clock();       //initilation of the variables
    bloom_size=atoi(argv[1]);
    num_threads=atoi(argv[2]);
    num_restarts=atoi(argv[3]);
    port=atoi(argv[4]);
    num_sections = bloom_size/BLOOM_FILTER_DIVISION;
    if(bloom_size%BLOOM_FILTER_DIVISION!=0)
    {
        num_sections++;
    }

    logfile=(char*)calloc(sizeof(argv[5]),sizeof(char));
    strcpy(logfile,argv[5]);

    if(num_threads>MAX_THREADS||num_threads<1)          //check for too many threads
    {
        while(temp_num_threads>MAX_THREADS||temp_num_threads<1) //until insert correct number
        {
            cout<<">>To many threads may .avoid too many threads (maximum "<<MAX_THREADS<<")"<<endl;
            cout<<">>Insert number of threads : ";
            cin>>temp_num_threads;  //take input
        }
        num_threads= temp_num_threads;
    }
    setEasyMode();      //set oracle operation
    initSeed(seed);
    initAlloc(malloc);
    bloom_filter.bloom_filter_allocation(bloom_size,num_hash);//call the function for allocate filter
    file_statistics_output.open(logfile);                   //file for thread statistics
    ptr->thread_repeats=num_restarts;                       //set variables for the threads
    ptr->num_hashing=num_hash;
    ptr->sections=num_sections;
    ptr->thbloom_size=bloom_size;
    ser_th_ptr->num_hashing=num_hash;                       //set variables for server thread
    ser_th_ptr->port_server_thr=port;
    ser_th_ptr->sections=num_sections;
    ser_th_ptr->thbloom_size=bloom_size;
    ser_th_ptr->repeats=num_restarts;
    ser_th_ptr->threads=num_threads;
    ser_th_ptr->seed=seed;
    pthread_mutex_init(&mutex_file_statistics_output, NULL);//initiate mutexes
    pthread_mutex_init(&mutex_founded_word, NULL);
    pthread_mutex_init(&mutex_end_of_program, NULL);
////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------INTERNET CONNECTION OPERATION---------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(client_mode==true)           //if the program works firts as a client
    {
       cout<<">>Insert for connection with server : ";
       cin>>client_port;                                //insert port for connection
       cout<<">>Connection with server : {"<<address<<"} through port : ["<<client_port<<"]......"<<endl;
       if((client_sock = socket(PF_INET , SOCK_STREAM , 0)) < 0)            //create socket
       {
           cout<<">>Error ! Cannot create socket for Internet connection (client)..."<<endl;
           exit(EXIT_FAILURE);
       }
       if((rem_client = gethostbyname(address)) == NULL)            //get host by name
        {
        /*  Find server  address */
           cout<<">>Error ! Cannot find server for Internet connection (client)..."<<endl;
           exit(EXIT_FAILURE);
        }
        server.sin_family = AF_INET ;               //set variables
        /* I n t e r n e t domain */
        memcpy (&server.sin_addr,rem_client->h_addr,rem_client->h_length) ;
        server.sin_port = htons (client_port) ;
        if (connect(client_sock,serverptr,sizeof(server)) < 0)          //connection to server
        {
            cout<<">>Error ! Cannot connect with server :"<<address<<",port :"<<client_port<<" (client)..."<<endl;
            exit(EXIT_FAILURE);
        }
        else                                //connection fail
        {
            cout<<">>Connection with :"<<address<<" established,port:"<<client_port<<endl;
        }
        if ( read ( client_sock , buf , sizeof(buf)) < 0)         //read information from server
        {
            cout<<">>Error ! Cannot read from server :"<<address<<",port :"<<client_port<<" (client)..."<<endl;
	     close(client_sock);                 //close socket
        }
        i=0;
        k=0;
        mm=0;
        check_argum_from_serv=0;
        while(buf[i]!='\0')     //read all buffer
        {
            temp[k]=buf[i];
            k++;
            if(buf[i]=='@')     //the mark for separate the words
            {
                temp[k-1]='\0';
                if(mm==0)       //check for bloom size
                {
                    if(bloom_size==atoi(temp))
                    {
                         check_argum_from_serv++;
                    }
                }
                if(mm==1)   //check for number of threads
                {
                    if(num_threads==atoi(temp))
                    {
                        check_argum_from_serv++;
                    }
                }
                if(mm==2)   //check for number of restarts
                {
                    if(num_restarts==atoi(temp))
                    {
                        check_argum_from_serv++;
                    }
                }
                if(mm==3)   //check for number of hush functions
                {
                    if(num_hash==atoi(temp))
                    {
                       check_argum_from_serv++;
                    }
                }
                k=0;
                mm++;
            }
            i++;
        }
        temp[k]='\0';               //make it string
        if(seed==atoi(temp))    //check for initiator seed
        {
            check_argum_from_serv++;
        }
        if(check_argum_from_serv==5)    //if all arguments matches bloom_array
        {
            cout<<">>Arguments matches ,passing bloom filter...."<<endl;
            if ( write ( client_sock , "YES" , sizeof("YES"))<0)    //alert server
            {
                cout<<">>Error in client,cannot write to channel.."<<endl;
                pthread_exit(NULL);
            }
            j=0;
            while(1)
            {
                if ( (rsize_bloom=read ( client_sock , buf , sizeof(buf))) < 0) //read information from server
                {
                    cout<<">>Error ! Cannot read from server :"<<address<<",port :"<<client_port<<" (client)..."<<endl;
                    close(client_sock);                 //close socket
                    exit(EXIT_FAILURE);
                }
                count_rsize=0;
                while(count_rsize<rsize_bloom)    //read each digit of the output of pipe
                {
                    if(j==bloom_size)
                    {
                        end_read=true;
                        break;
                    }
                    bloom_filter.bloom_array[j]=buf[count_rsize];
                    count_rsize++;
                    j++;
                }
                if(end_read==true)
                {
                    break;
                }
            }
            cout<<">>Data has passed,close connection...."<<endl;
        }
        else        //else exit program
        {
            cout<<">>Arguments don't match with server's,program terminates...."<<endl;
            if ( write ( client_sock , "NO" , sizeof("NO"))<0)  //alert server
            {
                cout<<">>Error in client,cannot write to channel.."<<endl;
                pthread_exit(NULL);
            }
            exit(EXIT_FAILURE);
        }
        close(client_sock);                 //close socket

   }
////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------STARTS MAIN PROGRAMM OPERATION--------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////////////////////////////
    total_threads =(pthread_t*)malloc(num_threads * sizeof(pthread_t)); //allocate memory
    mutex_array =(pthread_mutex_t *)malloc((num_sections)*sizeof(pthread_mutex_t));//allocate memory mutexes
    if (total_threads == NULL)      //allocate memory for threads
    {
        cout<<">>Error in main!Cannot allocate memory for "<<num_threads<<" threads.."<<endl;//error due allocation
        exit(EXIT_FAILURE);
    }
    if (error_thread = pthread_create(&server_thread, NULL,server_thread_operation, (void *) ser_th_ptr))//create server
    {
        cout<<">>Error in main,cannot create server thread...."<<endl; //check for error
        exit(EXIT_FAILURE);
    }
    for (i=0 ; i<num_threads; i++)//create the threads
    {
        if (error_thread = pthread_create(total_threads+i, NULL,thread_find_word_operation, (void *) ptr))//check for error
        {
            cout<<">>Error in main,cannot create thread number "<<i<<endl;
            exit(EXIT_FAILURE);
        }
    }
    for (i=0 ; i<num_threads ; i++)//for every thread
    {
        if (error_thread = pthread_join(*(total_threads+i), NULL))//wait for termination
        {
            cout<<">>Error in main,cannot join thread number "<<i<<endl;
            exit(EXIT_FAILURE);
        }
    }
    pthread_mutex_lock(&mutex_end_of_program);                            //lock mutex to check if program is over
        end_of_programm=true;               //inform server for termination
    pthread_mutex_unlock(&mutex_end_of_program);                               //lock mutex to check if program is over
    shutdown(serversock,SHUT_RDWR);     //close server
    if (error_thread = pthread_join(server_thread, NULL))//wait for server termination
    {
        cout<<">>Error in main,cannot join server thread "<<endl;
        exit(EXIT_FAILURE);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------FREE MEMORY AND TERMINATE PROGRAM--------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
    file_statistics_output << "\nTHREAD ID   "; //write to file same words
    file_statistics_output << "USED  ";
    file_statistics_output << "REJECTED   ";
    file_statistics_output << " BF % ";
    bloom_filter.delete_bloom();                //delete bloom
    file_statistics_output.close();             //close file
    free(total_threads);                        //free matrix
    endd = clock();                             //end clock
    time_spent = (double)(endd - beginn) / CLOCKS_PER_SEC;//set time used then print statistics
    print_final_statistics_message(argc,argv[6],bloom_size,num_threads,num_restarts,port,logfile,num_hash,address,seed,founded_word,time_spent,total_word_used,total_word_wasted,perc_bloom,num_connection);
    pthread_mutex_destroy(&mutex_file_statistics_output);//destroy mutexes
    pthread_mutex_destroy(&mutex_founded_word);
    pthread_mutex_destroy(&mutex_end_of_program);
    for(i=0;i<num_sections;i++)         //destroy matrix of mutexes
    {
        pthread_mutex_destroy(&mutex_array[i]);
    }
    cout<<">>Program terminated successfully..!"<<endl; //end of program
    return 0;
}


//////////////////////////////////
//        THREAD SERVER         //
//////////////////////////////////
void *server_thread_operation(void *arg)
{
    struct server_thread_data * arguments =(struct server_thread_data *) arg;    //arguments
    struct server_worker_thread_data *ser_wr_th_ptr=(server_worker_thread_data*)malloc(sizeof(server_worker_thread_data));
    int port=arguments->port_server_thr, error_thread,counter=0, newsockserver;  //and variables
    pthread_t *total_worker_threads;                                             //thread for workers
    total_worker_threads =(pthread_t*)malloc(NUM_WAIT_CONNECTION_Q * sizeof(pthread_t));//malloc
    if (total_worker_threads == NULL)                                            //check for error
    {
        cout<<">>Error in Server!Cannot allocate memory for "<<NUM_WAIT_CONNECTION_Q<<" threads.."<<endl;
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in server , client ;                                         //variables for internet connection
    socklen_t clientlen ;
    struct sockaddr * serverptr =( struct sockaddr *) & server ;
    struct sockaddr * clientptr =( struct sockaddr *) & client ;
    struct hostent * rem ;
    ser_wr_th_ptr->num_hashing=arguments->num_hashing;                          //pass arguments
    ser_wr_th_ptr->sections=(arguments->sections);                              //to variables
    ser_wr_th_ptr->repeats=arguments->repeats;                                  //for the server
    ser_wr_th_ptr->thbloom_size=arguments->thbloom_size;                        //and then
    ser_wr_th_ptr->threads=arguments->threads;                                  //for the workers
    ser_wr_th_ptr->seed=arguments->seed;
    /* Create socket */
    if ((serversock = socket(PF_INET, SOCK_STREAM, 0)) < 0)                     //check for error
    {
        cout<<">>Error ! Cannot create socket for Internet connection (Server Thread)..."<<endl;
        exit(EXIT_FAILURE);
    }
    /* Internet domain */
    server.sin_family = AF_INET;                                                //for the domain of server
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);
    /* Bind socket to address */
    if (bind(serversock, (struct sockaddr *)serverptr, sizeof(server)) < 0)     //check for error
    {
        cout<<">>Error ! Cannot bind socket for Internet connection (Server Thread)..."<<endl;
        exit(EXIT_FAILURE);
    }
    if (listen(serversock, NUM_WAIT_CONNECTION_Q) < 0)                          //listen function ,check for error
    {
        cout<<">>Error ! Cannot listen socket for Internet connection (Server Thread)..."<<endl;
        exit(EXIT_FAILURE);
    }
    cout<<">>Server Thread :["<<pthread_self()<<"] listening for connections to port: "<<port<<endl;//everything is ok
    while(counter<NUM_WAIT_CONNECTION_Q)                                         //server supports a specific amount of clients
    {
        if (( newsockserver = accept( serversock , clientptr , &clientlen) )< 0) //wait for connection
        {
            break;
        }
        pthread_mutex_lock(&mutex_end_of_program);                               //lock mutex to check if program is over
        if(end_of_programm==true)                                                //end server
        {
            pthread_mutex_unlock(&mutex_end_of_program);
            break;
        }
        else
        {
            pthread_mutex_unlock(&mutex_end_of_program);                            //unlock mutex
        }
        ser_wr_th_ptr->newsocket=newsockserver;                                 //pass new socket to worker
        if (error_thread = pthread_create(total_worker_threads+counter, NULL,server_worker_thread_operation,(void *) ser_wr_th_ptr))//check error
        {
            cout<<">>Error in main,cannot create thread number "<<counter<<endl;//create new worker thread
            exit(EXIT_FAILURE);
        }
        counter++;                                                              //counter of connection for statistics
        num_connection++;                                                       //counter
    }
    close ( newsockserver );                                                    //close socket
    cout<<">>Server Thread :["<<pthread_self()<<"]  exiting..."<<endl;          //ends
    free(total_worker_threads);
    pthread_exit(NULL);
}
//////////////////////////////////
//        THREAD WORKER         //
//////////////////////////////////
void *server_worker_thread_operation(void *arg)
{
    struct server_worker_thread_data * arguments =(struct server_worker_thread_data *) arg;
    int newsock =arguments->newsocket, i,tmp_i, counter_arguments=4;//arguments
    char buf_arguments_server[1001],temp[100];                      //and variables
    sprintf(temp, "%d", arguments->thbloom_size);
    for(i=0;i<strlen(temp);i++)                                     //here creates string to pass to client
    {
        buf_arguments_server[i]=temp[i];                            //to check the arguments,the size of bloom
    }
    buf_arguments_server[i]='@';
    tmp_i=i+1;
    sprintf(temp, "%d", arguments->threads);
    for(i=0;i<strlen(temp);i++)                                      //number of threads
    {
        buf_arguments_server[tmp_i]=temp[i];
        tmp_i++;
    }
    buf_arguments_server[tmp_i]='@';                                 //number of repeats
    tmp_i=tmp_i+1;
    sprintf(temp, "%d", arguments->repeats);
    for(i=0;i<strlen(temp);i++)
    {
        buf_arguments_server[tmp_i]=temp[i];
        tmp_i++;
    }
    buf_arguments_server[tmp_i]='@';                                 //number of hush functions
    tmp_i=tmp_i+1;
    sprintf(temp, "%d", arguments->num_hashing);
    for(i=0;i<strlen(temp);i++)
    {
        buf_arguments_server[tmp_i]=temp[i];
        tmp_i++;
    }
    buf_arguments_server[tmp_i]='@';                                //number of seed for oracle
    tmp_i=tmp_i+1;
    sprintf(temp, "%d", arguments->seed);
    for(i=0;i<strlen(temp);i++)
    {
        buf_arguments_server[tmp_i]=temp[i];                        //we use '@' to separate the arguments
        tmp_i++;
    }                                                               //finally example: 120000@12@12@3@444
    for(i=0;i<arguments->sections;i++)                              //lock all mutexes
    {
        pthread_mutex_lock(&mutex_array[i]);
    }
    cout<<">>--------------->Connection With Client<----------------------<<"<<endl;
    cout<<">>Server Thread :["<<pthread_self()<<"] accepted connection"<<endl;
    cout<<">>Server Thread :["<<pthread_self()<<"] locking all mutexes...."<<endl;
    cout<<">>Server Thread :["<<pthread_self()<<"] established connection"<<endl;
    if ( write ( newsock , buf_arguments_server , sizeof(buf_arguments_server))<0)//write the string to channel
    {
        cout<<">>Error in server,cannot write to channel.."<<endl;  //check error
        pthread_exit(NULL);
    }
    if ( read ( newsock ,  buf_arguments_server , sizeof( buf_arguments_server))<0) //wait reply from client
    {
        cout<<">>Error in server,cannot read from channel.."<<endl; //check error
        pthread_exit(NULL);
    }
    if(strcmp( buf_arguments_server,"YES")==0)                      //if reply is positive
    {
        cout<<">>Server Thread :["<<pthread_self()<<"] data transferring........ "<<endl;   //proceed
        tmp_i=0;
        for(i=0;i<arguments->thbloom_size;i++)                      //pass the bloom filter to channel
        {
            buf_arguments_server[tmp_i]=bloom_filter.bloom_array[i];
            if(tmp_i>=999)                                          //part by part
            {
                buf_arguments_server[tmp_i]='\0';                   //as string
                if ( write ( newsock , buf_arguments_server , sizeof(buf_arguments_server))<0)//passing
                {
                         cout<<">>Error in server,cannot write to channel.."<<endl; //check error
                        pthread_exit(NULL);
                    }
                tmp_i=-1;
            }
            tmp_i++;
        }                                                           //filter passed
        cout<<">>Server Thread :["<<pthread_self()<<"] transfered all data!"<<endl;//OK
    }
    else    //if reply is negative
    {
        cout<<">>Server Thread :["<<pthread_self()<<"] don't send any data....... "<<endl;//cout
    }
    cout<<">>Server Thread :["<<pthread_self()<<"] closing connection"<<endl;
    cout<<">>Server Thread :["<<pthread_self()<<"] unlocked all mutexes"<<endl;
    cout<<">>--------------->End Connection With Client<------------------<<"<<endl;
    for(i=0;i<arguments->sections;i++)                             //unlock mutexes
    {
        pthread_mutex_unlock(&mutex_array[i]);
    }
    close(newsock);                                                //close socket
    pthread_exit(NULL);                                            //ends
}


//////////////////////////////////
//      THREAD FIND WORD        //
//////////////////////////////////
void *thread_find_word_operation(void *arg)
{
    struct thread_data * arguments =(struct thread_data *) arg;     //arguments and variables
    List *thread_Word_List=new List;
    int repeats = (arguments->thread_repeats);
    int hash_num =(arguments->num_hashing),num_mutex = (arguments->sections),bloom_size = (arguments->thbloom_size);
    int i,hold,j,total_words=0,k=0,l,check,m,n,pass,section,temp_section,bits_used=0,bloom_byte,key;
    int bit_of_section,hash_result,already_used_words=0,string_length = RANDOM_STRING_LENGTH;
    int *hash_matrix =(int *) malloc(hash_num*sizeof(int));
    unsigned int rseed=time(NULL);
    const char **word_array=NULL,* pointer;
    char rand_word[string_length],test,compare_word;
    bool no_word_founded=false;
    for(j=0;j<repeats;j++)                                          //repeat the thread's operation
    {
        for(i=0;i<string_length;i++)                                //create random word to begin
        {
            rseed = (rseed+i+(rseed+pthread_self()))%(10000000);    //random seed
            key=rand_r(&rseed) % (126 + 1 - 33) + 33;               //each letter
            rand_word[i]=key;
        }
        rand_word[i]='\0';                                          //make a string
        word_array=oracle(rand_word);                               //begin search
        while(word_array!=NULL)                                     //while thread finds word or
        {                                                           //something else occurs
           i=0;
           while(word_array[i]!=NULL)                               //for every element of oracle return array
           {
                for(l=0;l<hash_num;l++)                             //find each hash result
                {
                    hash_result=(hash_by(l,word_array[i])%((bloom_size*CHAR_BIT)));
                    hash_matrix[l]=hash_result;                     //save it to matrix
                }
                for(pass = 1; pass <= (hash_num-1); pass++)         //sort the hash array
                {
                    for(m = 0; m <= (hash_num-2); m++)
                    {
                        if(hash_matrix[m] > hash_matrix[m + 1])
                        {
                            hold = hash_matrix[m];
                            hash_matrix[m] = hash_matrix[m + 1];
                            hash_matrix[m + 1] = hold;
                        }
                    }
                }
                temp_section = -100;
                for(n=0;n<hash_num;n++)                             //lock the proper locks
                {
                    section=hash_matrix[n]/(BLOOM_FILTER_DIVISION*CHAR_BIT);
                    if(section!=temp_section)                       //avoid lock the already locked
                    {                                               //in case of the same hash result
                        pthread_mutex_lock(&mutex_array[section]);
                    }
                    temp_section=section;
                }
                check=0;
                for(n=0;n<hash_num;n++)                             //bloom operation
                {
                    if(temp_section!=hash_matrix[n])                //avoid same hash result
                    {
                        test=0x01;
                        bloom_byte=hash_matrix[n]/CHAR_BIT;
                        bit_of_section=CHAR_BIT-(hash_matrix[n]%CHAR_BIT);      //find number of bit
                        test=(test<<(bit_of_section-1));
                        compare_word=bloom_filter.bloom_array[bloom_byte];
                        bloom_filter.bloom_array[bloom_byte]=(bloom_filter.bloom_array[bloom_byte]|test);
                        if(compare_word!=bloom_filter.bloom_array[bloom_byte])    //if has change
                        {                                             //count how many times(each hash)
                            check++;
                            bits_used++;
                        }
                    }
                    temp_section=hash_matrix[n];                    //store previous result to compare later
                }
                temp_section = -100;
                for(n=0;n<hash_num;n++)                             //lock the proper locks
                {
                    section=hash_matrix[n]/(BLOOM_FILTER_DIVISION*CHAR_BIT);
                    if(section!=temp_section)                       //avoid lock the already locked
                    {                                               //in case of the same hash result
                        pthread_mutex_unlock(&mutex_array[section]);
                    }
                    temp_section=section;
                }
                if(check>0)                                          //at least one change
                {
                    thread_Word_List->insert_words_list(word_array[i]);             //insert word
                }
                else                                                //else
                {
                    already_used_words++;                           //count rejected words
                }
                i++;
           }
           free((char *)word_array[i]);                             //free matrix[i]==NULL
           if(thread_Word_List->check_empty_list()==true)           //if list empty
           {                                                        //retry search
               break;
           }
            pointer=thread_Word_List->return_next_word_list();      //take next word
            word_array=oracle(pointer);                             //check it to oracle
            total_words++;                                          //total checked words
            if(total_words>20&&(total_words%20==0))                 //check if other threads finds the word
            {
            pthread_mutex_lock(&mutex_founded_word);                //lock
                if(founded_word == true)                            //check
                {
                    pthread_mutex_unlock(&mutex_founded_word);
                    break;
                }
                else
                {
                    pthread_mutex_unlock(&mutex_founded_word);              //unlock
                }
            }
        }
        if(word_array==NULL)                                        //if finds the word
        {
            no_word_founded=true;                                   //ends search
            break;
        }
    }
    if(no_word_founded==true)                                       //finds word
    {                                                               //lock
        pthread_mutex_lock(&mutex_founded_word);
            if(founded_word==false)                                 //other thread does not finds it first
            {
                founded_word = true;
                cout<<">>Thread :["<<pthread_self()<<"] found secret word int the ["<<1+j<<"]st try.."<<endl;
                cout<<">>Secret word is :      "<<pointer<<"  !!!!!!!!!!"<<endl;
            }
            else                                                    //else
            {
               cout<<">>Thread :["<<pthread_self()<<"] also found secret word ,exiting..."<<endl;
            }
        pthread_mutex_unlock(&mutex_founded_word);                  //unlock
    }
    else                                                            //don't finds word
    {
        cout<<">>Thread :["<<pthread_self()<<"] could not found secret word ,exiting..."<<endl;
    }
    pthread_mutex_lock(&mutex_file_statistics_output);              //lock file
        file_statistics_output << pthread_self();                   //write statistics
        file_statistics_output << "  ";
        file_statistics_output << total_words;
        file_statistics_output << "  ";
        file_statistics_output << already_used_words;
        file_statistics_output << "  ";
        file_statistics_output << ((((float)bits_used)/((float)(bloom_size*CHAR_BIT)))*100);
        file_statistics_output << "\n";
        total_word_used=total_word_used+total_words;
        total_word_wasted=total_word_wasted+already_used_words;
        perc_bloom=perc_bloom+bits_used;
    pthread_mutex_unlock(&mutex_file_statistics_output);            //unlock file
    thread_Word_List->delete_list();                                //free memory and ends
    delete thread_Word_List;
    free(hash_matrix);
    pthread_exit(NULL);
}


