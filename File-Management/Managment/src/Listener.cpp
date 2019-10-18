#include "Listener.h"

////////////////////////
//     CONSTRUCTOR    //
////////////////////////
Listener::Listener()
{

}

///////////////////////////////
//     Listener_Operation    //
///////////////////////////////
void Listener::Listener_Operation(int *man_lis_pipe,char* path)
{
    dup2 (man_lis_pipe[WRITE],1);       //Set stdout of listener to pipe
    close(2);                           //close messages pf inotifywait
    execlp("inotifywait","inotifywait","-m","-e","create",path,NULL); //execute
    cout<<">>Listener:Error executing ""execlp""...\n>>End of program..."<<endl;//case of error
    exit(1);
}

