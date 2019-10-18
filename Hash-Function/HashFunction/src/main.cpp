#include<stdio.h>
#include<cstdlib>
#include<string.h>
#include"hashingtable.h"

using namespace std;


int main(int argc , char **argv){

    hashtable h;
    h.setmatrixdim(8);
    h.sethashmatrix();
    char* command;
    char *num=NULL,*nam=NULL;
    char *las=NULL,*tow=NULL,*bil=NULL;
    char *str;
    int error,i;
    cout<<">> ";
    str=new char [152];
    gets(str);
    command = strtok (str," ,.-");
    while(strcmp(command,"e")!=0){
        error=0;
        i=0;
        if(strcmp(command,"l")==0){
        }
        else if(strcmp(command,"i")==0){
            command = strtok (NULL," ,.-");
            num=command;
            if(num!=NULL)
                i++;
            command = strtok (NULL, " ");
            nam=command;
            if(nam!=NULL)
                i++;
            command = strtok (NULL, " ");
            las=command;
            if(las!=NULL)
                i++;
            command = strtok (NULL, " ");
            tow=command;
            if(tow!=NULL)
                i++;
            command = strtok (NULL, " ");
            bil=command;
            if(bil!=NULL)
                i++;
            if(i!=5)
                cout<<">> Missing arguments in the input.."<<endl;
            else
                h.insertrecord(num,nam,las,tow,bil);
            str=new char [152];
        }
        else if(strcmp(command,"d")==0){
            command = strtok (NULL," ,.-");
            num=command;
             if(num==NULL)
                cout<<">> Missing arguments in the input.."<<endl;
            else
                h.deleterecord(num);
        }
        else if(strcmp(command,"q")==0){
            command = strtok (NULL," ,.-");
            num=command;
             if(num==NULL)
                cout<<">> Missing arguments in the input.."<<endl;
            else
                h.query(num);
        }
        else if(strcmp(command,"p")==0){
            command = strtok (NULL," ,.-");
            num=command;
             if(num==NULL)
                cout<<">> Missing arguments in the input.."<<endl;
            else
                h.population(num);
        }
        else if(strcmp(command,"t")==0){
            command = strtok (NULL," ,.-");
            num=command;
            if(num==NULL)
                cout<<">> Missing arguments in the input.."<<endl;
            else
                h.top(atoi(num));
        }
        else if(strcmp(command,"s")==0){
            command = strtok (NULL," ,.-");
            num=command;
             if(num==NULL)
                cout<<">> Missing arguments in the input.."<<endl;
            else
                h.sum(num);
        }
        else if(strcmp(command,"ft")==0){
            command = strtok (NULL," ,.-");
            num=command;
            if(num!=NULL)
                i++;
            command = strtok (NULL," ,.-");
            nam=command;
            if(nam!=NULL)
                i++;
            if(i!=2)
                cout<<">> Missing arguments in the input.."<<endl;
            else
                h.findtown(num,atoi(nam));
        }
        else if(strcmp(command,"fts")==0){
            h.findtopspender();
        }
        else if(strcmp(command,"min/max")==0){
            h.min_max();
        }
        else if(strcmp(command,"e")==0){
            h.exit();
            break;
        }
        else {
            cout<<">> Error this command does not exist!"<<endl;
        }
        cout<<">> ";
        //h.pr();
        str=new char [152];
        gets(str);
        command = strtok (str," ,.-");
    }
    return 0;
}


