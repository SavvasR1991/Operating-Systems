#include "processes.h"
#include "Operations.h"
#include "delayTime.h"


void Control(int type,int numOfMachineParts){

    int sem_START_PROCESSES = semget(SEM_START_PROCESSES,1,PERMS|IPC_CREAT);
    int sem_PREPARED_PROCESSES = semget(SEM_PREPARED_PROCESSES,1,PERMS|IPC_CREAT);
    int sem_painter = semget(SEM_PAINTER,1,PERMS|IPC_CREAT);
    int sem_construction = semget(SEM_CONSTRUCTION,1,PERMS|IPC_CREAT);

    int shm_CONSTUCTION;
    int shm_CONTROL;
    int i;
    int ID;
    int sem_CONTROL;
    
    switch (type){
        case 1:
            sem_CONTROL = semget(SEM_CONTROL1,1,PERMS|IPC_CREAT);
            break;
        case 2:
            sem_CONTROL = semget(SEM_CONTROL2,1,PERMS|IPC_CREAT);
            break;
        case 3:
            sem_CONTROL = semget(SEM_CONTROL3,1,PERMS|IPC_CREAT);
        default:
            break;
    }
    
    shm_data_1 *data_construction;
    shm_data_1 *data_control;

    shm_CONSTUCTION = shmget(SHM_CONSTRUCTION,sizeof(shm_data_1),PERMS|IPC_CREAT);
    data_construction = (shm_data_1 *)shmat(shm_CONSTUCTION,(void *)0,0);

    shm_CONTROL = shmget(SHM_CONTROL,sizeof(shm_data_1),PERMS|IPC_CREAT);
    data_control = (shm_data_1 *)shmat(shm_CONTROL,(void *)0,0);

    cout<<"->Control "<<type<<" created with PID = ["<<getpid()<<"]..."<<endl;
    up(sem_PREPARED_PROCESSES);
    down(sem_START_PROCESSES);
    up(sem_START_PROCESSES);

    //////////////////// Control Processes Execution ///////////////////////

    for(i=0;i<numOfMachineParts;i++){
        down(sem_CONTROL);
        ID = data_control->ID;
        cout<<"->Control "<<type<<" with PID = ["<<getpid()<<"] received ID =  ["<<ID<<"]..."<<endl;
        data_construction->ID = ID;
        data_construction->type = type;
        cout<<"->Control "<<type<<" with PID = ["<<getpid()<<"] sends ID =  ["<<ID<<"] to Constuction..."<<endl<<endl;
        up(sem_construction);
        down(sem_CONTROL);
        up(sem_painter);
    }

    cout<<"->Control "<<type<<" terminated with PID = ["<<getpid()<<"]...\n"<<endl;

    ////////////////////////////////////////////////////////////////////////
    exit(EXIT_SUCCESS);
}
