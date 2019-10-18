#include "processes.h"
#include "Operations.h"
#include "delayTime.h"


void Part(int type,int numOfMachineParts){

    int sem_START_PROCESSES = semget(SEM_START_PROCESSES,1,PERMS|IPC_CREAT);
    int sem_PREPARED_PROCESSES = semget(SEM_PREPARED_PROCESSES,1,PERMS|IPC_CREAT);
    int sem_PAINTER = semget(SEM_PAINTER,1,PERMS|IPC_CREAT);
    int sem_PART = semget(SEM_PART,1,PERMS|IPC_CREAT);
    int shm_PAINTER;
    int ID = 0;
    int pendingTime = 0;
    int i = 0;
    char partType[MAX_CHAR_TYPE];
    char ID_String[2];
    shm_data_1 *data_painter;

    srand (time(NULL)+type*numOfMachineParts);

    shm_PAINTER = shmget(SHM_PAINTER,sizeof(shm_data_1),PERMS|IPC_CREAT);
    data_painter = (shm_data_1 *)shmat(shm_PAINTER,(void *)0,0);

    sprintf(ID_String, "%d", type);
    strcpy(partType,"Part ");
    strcat(partType,ID_String);

    cout<<"->Part "<<type<<" created with PID = ["<<getpid()<<"]..."<<endl;
    up(sem_PREPARED_PROCESSES);
    down(sem_START_PROCESSES);
    up(sem_START_PROCESSES);

    //////////////////// Part Processes Execution //////////////////////////

    for(i=0;i<numOfMachineParts;i++){
        ID = rand()%10000;

        down(sem_PART);
        cout<<"->Part "<<type<<" with PID = ["<<getpid()<<"] sents ID = "<<ID<<endl;
        data_painter->ID = ID;
        data_painter->type = type;
        data_painter->piece = i;
        data_painter->time = PAINTER_TIME_PART1_MS;
        strcpy(data_painter->communication,partType);
        up(sem_PAINTER);

    }

    cout<<"->Part "<<type<<" terminated with PID = ["<<getpid()<<"]..."<<endl;

    ////////////////////////////////////////////////////////////////////////
    exit(EXIT_SUCCESS);
}


