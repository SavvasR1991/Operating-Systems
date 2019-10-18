#include "processes.h"
#include "Operations.h"
#include "delayTime.h"
#include "OperationsStatistics.h"

void Contruction(int numOfMachineParts){

    int sem_START_PROCESSES = semget(SEM_START_PROCESSES,1,PERMS|IPC_CREAT);
    int sem_PREPARED_PROCESSES = semget(SEM_PREPARED_PROCESSES,1,PERMS|IPC_CREAT);
    int sem_construction = semget(SEM_CONSTRUCTION,1,PERMS|IPC_CREAT);
    int shm_CONSTUCTION;
    int shm_STATISTICS;
    int ID;
    int sem_CONTROL;
    int type;
    int part1Counter = 0;
    int part2Counter = 0;
    int part3Counter = 0;
    int *currentPart;
    int *currentPartCounter;
    shm_data_1 *data_construction;
    shm_data_2 *data_statistics;

    shm_CONSTUCTION = shmget(SHM_CONSTRUCTION,sizeof(shm_data_1),PERMS|IPC_CREAT);
    data_construction = (shm_data_1 *)shmat(shm_CONSTUCTION,(void *)0,0);
    
    shm_STATISTICS = shmget(SHM_STATISTICS,sizeof(shm_data_2),PERMS|IPC_CREAT);
    data_statistics = (shm_data_2 *)shmat(shm_STATISTICS,(void *)0,0);

    cout<<"->Constuction created with PID = ["<<getpid()<<"]..."<<endl;
    up(sem_PREPARED_PROCESSES);
    down(sem_START_PROCESSES);
    up(sem_START_PROCESSES);

    ///////////////////// Contruction Process Execution ////////////////////
    
    
    
    
    for(int i =0;i<numOfMachineParts*3;i++){
        down(sem_construction);
        ID = data_construction->ID;
        type = data_construction->type;
    
        switch (type){
            case 1:
                sem_CONTROL = semget(SEM_CONTROL1,1,PERMS|IPC_CREAT);
                currentPart = data_statistics->part1;
                currentPartCounter = &part1Counter;
                break;
            case 2:
                sem_CONTROL = semget(SEM_CONTROL2,1,PERMS|IPC_CREAT);
                currentPart = data_statistics->part2;
                currentPartCounter = &part2Counter;
                break;
            case 3:
                sem_CONTROL = semget(SEM_CONTROL3,1,PERMS|IPC_CREAT);
                currentPart = data_statistics->part3;
                currentPartCounter = &part3Counter;
            default:
                break;
        }
        cout<<"->Construction with PID = ["<<getpid()<<"] received ID =  ["<<ID<<"] from Control "<<type<<"..."<<endl;
        currentPart[(*currentPartCounter)] = ID ;
        (*currentPartCounter)++;
        up(sem_CONTROL);
    }

    cout<<"->Construction terminated with PID = ["<<getpid()<<"]..."<<endl;
    
    ////////////////////////////////////////////////////////////////////////
    exit(EXIT_SUCCESS);
}
