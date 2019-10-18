#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <signal.h>
#include <string.h>
#include "processes.h"
#include "Operations.h"
#include "OperationsStatistics.h"

using namespace std;

int main (int argc, char** argv){
    cout<<"|----------------------PROGRAMM STARTS------------------------|"<<endl;

    if (argc != 2){
        cout<<"Please insert number of machine parts.."<<endl;  
        return 0;
    }
    int numOfMachineParts = atoi(argv[1]);

    int sem_START_PROCESSES;
    int sem_PREPARED_PROCESSES;
    int sem_painter;
    int sem_part;
    int sem_construction;
    int sem_control1;
    int sem_control2;
    int sem_control3;

    int shm_PAINTER;
    int shm_CONSTUCTION;
    int shm_CONTROL;
    int shm_STATISTICS;

    shm_data_1 *data_painter;
    shm_data_1 *data_construction;
    shm_data_1 *data_control;
    shm_data_2 *data_statistics;

    senum arg;

    pid_t pid;
    pid_t pid_array[8];
    
    int *part1;
    int *part2;
    int *part3;
   
    
    srand( time(NULL) );

    cout<<"|-------------------SHARED MEMORIES------------------|"<<endl;
    shm_PAINTER = shmget(SHM_PAINTER,sizeof(shm_data_1),PERMS|IPC_CREAT);
    data_painter = (shm_data_1 *)shmat(shm_PAINTER,(void *)0,0);
    memcpy(&(data_painter->communication),"NULL",sizeof("NULL"));
    data_painter->ID = 0;
    data_painter->piece = 0;
    cout<<"->Shared memory "<<shm_PAINTER<<" created"<<endl;

    shm_CONSTUCTION = shmget(SHM_CONSTRUCTION,sizeof(shm_data_1),PERMS|IPC_CREAT);
    data_construction = (shm_data_1 *)shmat(shm_CONSTUCTION,(void *)0,0);
    memcpy(&(data_construction->communication),"NULL",sizeof("NULL"));
    cout<<"->Shared memory "<<shm_CONSTUCTION<<" created"<<endl;

    shm_CONTROL = shmget(SHM_CONTROL,sizeof(shm_data_1),PERMS|IPC_CREAT);
    data_control = (shm_data_1 *)shmat(shm_CONTROL,(void *)0,0);
    memcpy(&(data_construction->communication),"NULL",sizeof("NULL"));
    cout<<"->Shared memory "<<shm_CONTROL<<" created"<<endl;
    
    shm_STATISTICS = shmget(SHM_STATISTICS,sizeof(shm_data_2),PERMS|IPC_CREAT);
    data_statistics = (shm_data_2 *)shmat(shm_STATISTICS,(void *)0,0);
    cout<<"->Shared memory "<<shm_STATISTICS<<" created"<<endl;
    
    cout<<"|-------------------SHARED MEMORIES------------------|"<<endl;

    cout<<"|----------------------SEMAPHORES--------------------|"<<endl;
    sem_painter = semget(SEM_PAINTER,1,PERMS|IPC_CREAT);             
    arg.val=0;                                                       
    semctl(sem_painter,0,SETVAL,arg);
    cout<<"->Semaphore "<<sem_painter<<" created"<<endl;

    sem_part = semget(SEM_PART,1,PERMS|IPC_CREAT);             
    arg.val=0;                                                       
    semctl(sem_part,0,SETVAL,arg);
    cout<<"->Semaphore "<<sem_part<<" created"<<endl;

    sem_construction = semget(SEM_CONSTRUCTION,1,PERMS|IPC_CREAT);             
    arg.val=0;                                                       
    semctl(sem_construction,0,SETVAL,arg);
    cout<<"->Semaphore "<<sem_construction<<" created"<<endl;

    sem_control1 = semget(SEM_CONTROL1,1,PERMS|IPC_CREAT);             
    arg.val=0;                                                       
    semctl(sem_control1,0,SETVAL,arg);  
    cout<<"->Semaphore "<<sem_control1<<" created"<<endl;

    sem_control2 = semget(SEM_CONTROL2,1,PERMS|IPC_CREAT);             
    arg.val=0;                                                       
    semctl(sem_control2,0,SETVAL,arg);  
    cout<<"->Semaphore "<<sem_control2<<" created"<<endl;

    sem_control3 = semget(SEM_CONTROL3,1,PERMS|IPC_CREAT);             
    arg.val=0;                                                       
    semctl(sem_control3,0,SETVAL,arg);  
    cout<<"->Semaphore "<<sem_control3<<" created"<<endl;

    sem_START_PROCESSES = semget(SEM_START_PROCESSES,1,PERMS|IPC_CREAT);             
    arg.val=0;                                                       
    semctl(sem_START_PROCESSES,0,SETVAL,arg);
    cout<<"->Semaphore "<<sem_START_PROCESSES<<" created"<<endl;

    sem_PREPARED_PROCESSES = semget(SEM_PREPARED_PROCESSES,1,PERMS|IPC_CREAT);             
    arg.val=0;                                                       
    semctl(sem_PREPARED_PROCESSES,0,SETVAL,arg);
    cout<<"->Semaphore "<<sem_PREPARED_PROCESSES<<" created"<<endl;
    cout<<"|----------------------SEMAPHORES--------------------|"<<endl;
    

    cout<<"|----------------------PROCESSES---------------------|"<<endl;
    pid = fork();
    pid_array[0]=pid;
    if(pid==0)
    {
        Part(1,numOfMachineParts);
    }
    pid = fork();
    pid_array[1]=pid;
    if(pid==0)
    {
        Part(2,numOfMachineParts);
        exit(EXIT_SUCCESS);
    }
    pid = fork();
    pid_array[2]=pid;
    if(pid==0)
    {
        Part(3,numOfMachineParts);
        exit(EXIT_SUCCESS);
    }
    pid = fork();
    pid_array[3]=pid;
    if(pid==0)
    {
        Painter(numOfMachineParts);
        exit(EXIT_SUCCESS);
    }
    pid = fork();
    pid_array[4]=pid;
    if(pid==0)
    {
        Control(1,numOfMachineParts);
        exit(EXIT_SUCCESS);
    }
    pid = fork();
    pid_array[5]=pid;
    if(pid==0)
    {
        Control(2,numOfMachineParts);
        exit(EXIT_SUCCESS);
    }
    pid = fork();
    pid_array[6]=pid;
    if(pid==0)
    {
        Control(3,numOfMachineParts);
        exit(EXIT_SUCCESS);
    }
    pid = fork();
    pid_array[7]=pid;
    if(pid==0)
    {
        Contruction(numOfMachineParts);
        exit(EXIT_SUCCESS);
    }
    
    for (int i=0;i<NUM_OF_PROCESSES;i++){
         down(sem_PREPARED_PROCESSES);//Wait processes to be prepared
    }
    cout<<"|----------------------PROCESSES---------------------|\n\n"<<endl;

    cout<<"|.........Press any key to start simulator...........|"<<endl;
    getchar();//Start simulator

    cout<<"\n\n|-----------------SIMULATOR EXECUTION----------------|"<<endl;
    up(sem_START_PROCESSES);
    for (int i = 0; i < NUM_OF_PROCESSES; i++) {
        while (waitpid(pid_array[i], NULL, 0) > 0);
    }//Wait for all processes to finish
    cout<<"|-----------------SIMULATOR EXECUTION----------------|"<<endl;
    cout<<"|-----------------STATISTICS OUTPUT------------------|"<<endl;
    part1 = data_statistics->part1;
    part2 = data_statistics->part2;
    part3 = data_statistics->part3;
    
    cout<<"\n----> Part 1 "<<endl;
    for(int i=0;i<numOfMachineParts;i++)
    {
    
        cout<<" ["<<i<<"] : "<<part1[i]<<endl;
    
    }
    cout<<endl;
    
    cout<<"\n----> Part 2 "<<endl;
    for(int i=0;i<numOfMachineParts;i++)
    {
    
        cout<<" ["<<i<<"] : "<<part2[i]<<endl;
    
    }
    cout<<endl;
    
    cout<<"\n----> Part 3 "<<endl;
    for(int i=0;i<numOfMachineParts;i++)
    {
    
        cout<<" ["<<i<<"] : "<<part3[i]<<endl;
    
    }
    
    cout<<"|-----------------STATISTICS OUTPUT------------------|"<<endl;

    cout<<"|---------------------CLEAN UP-----------------------|"<<endl;
    shmctl(shm_PAINTER,IPC_RMID,(struct shmid_ds*)0);
    shmctl(shm_CONSTUCTION,IPC_RMID,(struct shmid_ds*)0);
    shmctl(shm_CONTROL,IPC_RMID,(struct shmid_ds*)0);
    shmctl(shm_STATISTICS,IPC_RMID,(struct shmid_ds*)0);

    cout<<"->Shared memory "<<shm_PAINTER<<" cleared"<<endl;
    cout<<"->Shared memory "<<shm_CONTROL<<" cleared"<<endl;
    cout<<"->Shared memory "<<shm_CONSTUCTION<<" cleared"<<endl;
    cout<<"->Shared memory "<<shm_STATISTICS<<" cleared"<<endl;

    semctl(sem_painter,1,IPC_RMID,0);
    semctl(sem_construction,1,IPC_RMID,0);
    semctl(sem_control1,1,IPC_RMID,0);
    semctl(sem_control2,1,IPC_RMID,0);
    semctl(sem_control3,1,IPC_RMID,0);
    semctl(sem_START_PROCESSES,1,IPC_RMID,0);
    semctl(sem_PREPARED_PROCESSES,1,IPC_RMID,0);

    cout<<"->Semaphore "<<sem_painter<<" free"<<endl;
    cout<<"->Semaphore "<<sem_construction<<" free"<<endl;
    cout<<"->Semaphore "<<sem_control1<<" free"<<endl;
    cout<<"->Semaphore "<<sem_control2<<" free"<<endl;
    cout<<"->Semaphore "<<sem_control3<<" free"<<endl;
    cout<<"->Semaphore "<<sem_START_PROCESSES<<" free"<<endl;
    cout<<"->Semaphore "<<sem_PREPARED_PROCESSES<<" free"<<endl;
    cout<<"|---------------------CLEAN UP-----------------------|"<<endl;


    cout<<"|--------------------PROGRAMM TERMINATED---------------------|"<<endl;
    return 1;
}
