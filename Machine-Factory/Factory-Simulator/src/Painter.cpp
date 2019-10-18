#include "processes.h"
#include "Operations.h"
#include "delayTime.h"

void Painter(int numOfMachineParts){

    int sem_START_PROCESSES = semget(SEM_START_PROCESSES,1,PERMS|IPC_CREAT);
    int sem_PREPARED_PROCESSES = semget(SEM_PREPARED_PROCESSES,1,PERMS|IPC_CREAT);
    int sem_PART = semget(SEM_PART,1,PERMS|IPC_CREAT);
    int sem_PAINTER = semget(SEM_PAINTER,1,PERMS|IPC_CREAT);
    int sem_CONTROL1 = semget(SEM_CONTROL1,1,PERMS|IPC_CREAT);
    int sem_CONTROL2 = semget(SEM_CONTROL2,1,PERMS|IPC_CREAT);
    int sem_CONTROL3 = semget(SEM_CONTROL3,1,PERMS|IPC_CREAT);
    int sem_CONTROL_CURRENT;
    int shm_PAINTER;
    int shm_CONTROL;
    int i=0;
    int ID;
    int piece=0;
    int type;
    int delayPartTime = 0;
    int delayPainterTime = 0;
    char stdin_input[MAX_CHAR_TYPE];
    shm_data_1 *data_painter;
    shm_data_1 *data_control;

    shm_PAINTER = shmget(SHM_PAINTER,sizeof(shm_data_1),PERMS|IPC_CREAT);
    data_painter = (shm_data_1 *)shmat(shm_PAINTER,(void *)0,0);

    shm_CONTROL = shmget(SHM_CONTROL,sizeof(shm_data_1),PERMS|IPC_CREAT);
    data_control = (shm_data_1 *)shmat(shm_CONTROL,(void *)0,0);


    cout<<"->Painter created with PID = ["<<getpid()<<"]..."<<endl;
    up(sem_PREPARED_PROCESSES);
    down(sem_START_PROCESSES);
    up(sem_START_PROCESSES);
    up(sem_PART);

    //////////////////// Painter Process Execution /////////////////////////

    for(i=0;i<numOfMachineParts*3;i++){
        down(sem_PAINTER);
        type = data_painter->type;
        switch (type){
            case 1:
                delayPartTime = PAINTER_TIME_PART1_MS;
                sem_CONTROL_CURRENT = sem_CONTROL1;
                break;
            case 2:
                delayPartTime = PAINTER_TIME_PART2_MS;
                sem_CONTROL_CURRENT = sem_CONTROL2;
                break;
            case 3:
                delayPartTime = PAINTER_TIME_PART3_MS;
                sem_CONTROL_CURRENT = sem_CONTROL3;
                break;
            default:
                break;

        }
        delayPainterTime += delayPartTime;
        ID = data_painter->ID;
        piece = data_painter->piece;
        strcpy(stdin_input,data_painter->communication);
        cout<<"->Painter with PID = ["<<getpid()<<"] received from "<<stdin_input<<" the ["<<piece+1<<"] piece with ID = "<<ID<<endl;
        cout<<"->Painter with PID = ["<<getpid()<<"] sents to Control "<<type<<" part with ID =  "<<ID<<endl;
        data_control->piece = piece;
        data_control->ID = ID;

        up(sem_CONTROL_CURRENT);
        down(sem_PAINTER);

        up(sem_PART);
    }

    cout<<"->Painter terminated with PID = ["<<getpid()<<"]..."<<delayPainterTime <<endl;

    ////////////////////////////////////////////////////////////////////////    
    exit(EXIT_SUCCESS);
}
